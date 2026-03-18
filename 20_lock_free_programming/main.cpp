/*
 * ============================================================
 * Module 20 — Lock-Free Programming (C++17)
 * ============================================================
 *
 * Lock-free data structures guarantee system-wide progress:
 * even if a thread is stalled, other threads can still make
 * forward progress. This is critical for real-time and
 * low-latency systems where mutex contention is unacceptable.
 *
 * Key concepts:
 *
 * 1. Lock-free vs wait-free vs obstruction-free
 *    - Obstruction-free: one thread can complete if others suspend
 *    - Lock-free:        at least one thread always makes progress
 *    - Wait-free:        every thread completes in a bounded number of steps
 *    - Most practical structures are lock-free (not wait-free)
 *
 * 2. ABA problem
 *    - CAS reads value A, another thread changes A→B→A
 *    - The CAS succeeds even though the object was modified
 *    - Solutions: tagged pointers (version counter), hazard pointers,
 *      epoch-based reclamation
 *
 * 3. Lock-free stack (Treiber stack)
 *    - Push: new_node->next = head; CAS(head, new_node->next, new_node)
 *    - Pop:  old_head = head; CAS(head, old_head, old_head->next)
 *    - Vulnerable to ABA — use a version/tag to fix
 *
 * 4. Lock-free SPSC queue (single-producer, single-consumer)
 *    - Only one reader and one writer — simplest lock-free case
 *    - Uses two atomic indices: head_ (consumer) and tail_ (producer)
 *    - No CAS needed: each index is written by exactly one thread
 *    - Suitable for sensor/control pipelines in robotics
 *
 * 5. Memory reclamation
 *    - Deferred deletion (epoch-based reclamation): delete when no thread
 *      can be accessing the object
 *    - Hazard pointers: a thread publishes a pointer it is reading;
 *      no other thread may delete it while it is hazardous
 *    - In simple cases, avoid dynamic memory in lock-free structures
 *      by using fixed-size pool allocators
 *
 * 6. False sharing
 *    - Two threads write different data that happen to share a cache line
 *    - Causes cache-line ping-pong and severe performance degradation
 *    - Fix: align each thread-local variable to hardware_destructive_interference_size
 *
 * Build & run:
 *   make run MODULE=20_lock_free_programming
 * ============================================================
 */

#include <atomic>
#include <cassert>
#include <iostream>
#include <new>      // std::hardware_destructive_interference_size
#include <optional>
#include <thread>
#include <vector>

// ── 1. Lock-free stack (Treiber stack) ───────────────────────────────────────
// TODO: Implement template <typename T> class LockFreeStack:
//
//   struct Node { T data; Node* next; };
//   std::atomic<Node*> head_{nullptr};
//
//   void push(T val):
//     Node* n = new Node{std::move(val), nullptr};
//     n->next = head_.load(relaxed);
//     while (!head_.compare_exchange_weak(n->next, n, release, relaxed));
//
//   std::optional<T> pop():
//     Node* old = head_.load(acquire);
//     while (old && !head_.compare_exchange_weak(old, old->next, acquire, relaxed));
//     if (!old) return std::nullopt;
//     T val = std::move(old->data);
//     delete old;  // NOTE: safe only in absence of concurrent readers of old
//     return val;
//
// NOTE: This simplified version has the ABA problem and a reclamation issue
//       (old->data may be accessed after delete in concurrent pop).
//       See the ABA commentary below.

// ── 2. ABA problem demonstration ─────────────────────────────────────────────
// TODO: In comments, walk through the ABA scenario step-by-step for the stack:
//   Thread 1: reads head = A
//   Thread 2: pops A, pops B, pushes A back (with A->next = nullptr now)
//   Thread 1: CAS(head, A, B) succeeds — but B was already freed!
//
// TODO: Show the tagged-pointer fix:
//   struct TaggedPtr { Node* ptr; uintptr_t tag; };
//   std::atomic<TaggedPtr> head_;
//   Push/pop increment the tag on each CAS — prevents false matches.
//   Implement TaggedLockFreeStack if your platform supports 128-bit atomics,
//   or use __int128 / std::atomic<std::pair<Node*, uint64_t>>.

// ── 3. SPSC queue (single-producer / single-consumer) ────────────────────────
// TODO: Implement template <typename T, std::size_t N> class SPSCQueue:
//
//   std::array<T, N> buf_;
//   alignas(std::hardware_destructive_interference_size) std::atomic<std::size_t> head_{0};
//   alignas(std::hardware_destructive_interference_size) std::atomic<std::size_t> tail_{0};
//
//   bool push(const T& val):
//     size_t t = tail_.load(relaxed);
//     if ((t - head_.load(acquire) + 1) % N == 0) return false;  // full
//     buf_[t % N] = val;
//     tail_.store(t + 1, release);
//     return true;
//
//   std::optional<T> pop():
//     size_t h = head_.load(relaxed);
//     if (h == tail_.load(acquire)) return std::nullopt;  // empty
//     T val = buf_[h % N];
//     head_.store(h + 1, release);
//     return val;

// ── 4. False sharing ─────────────────────────────────────────────────────────
// TODO: Demonstrate false sharing:
//
//   struct BadCounters  { int a; int b; };         // a and b share a cache line
//   struct GoodCounters {
//     alignas(std::hardware_destructive_interference_size) int a;
//     alignas(std::hardware_destructive_interference_size) int b;
//   };
//
//   Spawn 2 threads: thread A increments counter.a 1e7 times,
//                    thread B increments counter.b 1e7 times.
//   Time both variants and print the elapsed time.
//   (Use std::chrono::high_resolution_clock.)

// ── 5. Integration test ───────────────────────────────────────────────────────
void demo_spsc() {
    // TODO: SPSCQueue<int, 64> q;
    //       Producer thread: push 0..999, signalling done when finished.
    //       Consumer thread: pop and accumulate values; verify sum = 0+1+...+999.
    //       Join both threads and print the sum.
}

int main() {
    std::cout << "=== 20: Lock-Free Programming ===\n\n";

    std::cout << "-- Lock-free stack --\n";
    // TODO: Push 1,2,3 onto LockFreeStack<int>. Pop all and print.
    // TODO: Concurrent push/pop: 4 threads push 250 items each;
    //       4 threads pop until empty. Verify total pop count = 1000.

    std::cout << "\n-- SPSC queue --\n";
    demo_spsc();

    std::cout << "\n-- False sharing --\n";
    // TODO: Run the BadCounters vs GoodCounters timing benchmark.

    return 0;
}
