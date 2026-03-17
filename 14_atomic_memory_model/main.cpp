/*
 * ============================================================
 * Module 14 — Atomics & Memory Model (C++17)
 * ============================================================
 *
 * The C++ memory model defines how threads observe each other's
 * memory writes. Without explicit synchronisation, the compiler
 * and CPU are free to reorder operations for performance.
 * Atomics provide the primitives to write correct, low-latency
 * concurrent code without heavy mutex locking.
 *
 * Key concepts:
 *
 * 1. std::atomic<T>
 *    - Operations on atomic variables are indivisible (no torn reads/writes)
 *    - Works with integral types, pointers, and trivially-copyable types
 *    - Operations: load(), store(), fetch_add(), fetch_sub(), exchange()
 *    - Shorthand: ++ -- += -= &= |= ^= are atomic on integral atomics
 *
 * 2. Memory orderings
 *    - memory_order_relaxed:    no ordering guarantees; only atomicity
 *    - memory_order_acquire:    no reads/writes after this can be moved before
 *    - memory_order_release:    no reads/writes before this can be moved after
 *    - memory_order_acq_rel:    both acquire and release (for RMW ops)
 *    - memory_order_seq_cst:    total sequential consistency (default; safest)
 *    - Acquire-release pair: release-store is visible before acquire-load
 *
 * 3. Compare-and-swap (CAS)
 *    - compare_exchange_weak(expected, desired)  — may spuriously fail (loop)
 *    - compare_exchange_strong(expected, desired) — no spurious failure
 *    - Foundation of most lock-free data structures
 *    - If CAS fails, `expected` is updated with the current value
 *
 * 4. atomic_flag
 *    - Guaranteed lock-free (unlike std::atomic<bool> on some platforms)
 *    - test_and_set() — sets flag and returns old value
 *    - clear()
 *    - Use for spinlocks and simple flags
 *
 * 5. std::atomic_thread_fence
 *    - Standalone fence — does not operate on any particular variable
 *    - Used to enforce ordering between non-atomic accesses in combination
 *      with atomic loads/stores
 *
 * 6. Happens-before relationship
 *    - If A happens-before B, all of A's side effects are visible to B
 *    - Established by: sequenced-before, synchronises-with, inter-thread HB
 *    - Release-store synchronises-with a subsequent acquire-load of the same var
 *
 * Build & run:
 *   make run MODULE=14_atomic_memory_model
 * ============================================================
 */

#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

// ── 1. Basic atomic operations ────────────────────────────────────────────────
void demo_atomic_counter() {
    std::atomic<int> counter{0};

    // TODO: Spawn 10 threads each calling counter.fetch_add(1, relaxed) 1000 times.
    //       Join all and print counter. It should be 10000.
    //       Explain why relaxed is sufficient here (no ordering needed, just atomicity).

    // TODO: Repeat with counter++ (seq_cst). Confirm same result.
    //       Explain the additional cost of seq_cst.
}

// ── 2. Spinlock using atomic_flag ─────────────────────────────────────────────
// TODO: Implement class Spinlock using std::atomic_flag:
//   - void lock()   — busy-loop on test_and_set(acquire)
//   - void unlock() — clear(release)
//   - Optionally implement try_lock()
//
// NOTE: This is a pedagogical exercise. In production code, prefer std::mutex
//       unless you have profiling evidence that the lock is never contended long.

void demo_spinlock() {
    // TODO: Protect a shared int with your Spinlock.
    //       Spawn 5 threads incrementing it 1000 times each. Print the final value.
}

// ── 3. Acquire-Release — producer/consumer flag ───────────────────────────────
void demo_acquire_release() {
    std::atomic<bool> ready{false};
    int data = 0;

    // TODO: Producer thread:
    //   data = 42;
    //   ready.store(true, memory_order_release);   // publishes data
    //
    // TODO: Consumer thread:
    //   while (!ready.load(memory_order_acquire));  // waits until ready
    //   assert(data == 42);  // guaranteed because of acquire-release pair
    //
    // TODO: In comments, explain why memory_order_relaxed on either side
    //       would make data = 42 NOT guaranteed.
}

// ── 4. Compare-and-swap — lock-free counter ───────────────────────────────────
void demo_cas() {
    std::atomic<int> value{0};

    // TODO: Implement a "bounded increment" that only increments if value < 10:
    //   int old_val = value.load(relaxed);
    //   while (old_val < 10) {
    //       if (value.compare_exchange_weak(old_val, old_val + 1, acq_rel, relaxed))
    //           break;   // success
    //       // old_val updated by CAS — retry
    //   }
    //
    // TODO: Spawn 20 threads each running the bounded increment.
    //       Final value should be exactly 10.
    //       Explain in comments why compare_exchange_weak is preferred in loops.
}

// ── 5. Memory fence ───────────────────────────────────────────────────────────
void demo_fence() {
    std::atomic<int> flag{0};
    int x = 0, y = 0;

    // TODO: Thread 1 (writer):
    //   x = 1; y = 2;
    //   std::atomic_thread_fence(memory_order_release);
    //   flag.store(1, memory_order_relaxed);
    //
    // TODO: Thread 2 (reader):
    //   while (flag.load(memory_order_relaxed) == 0);
    //   std::atomic_thread_fence(memory_order_acquire);
    //   assert(x == 1 && y == 2);  // guaranteed by fence pair
    //
    // TODO: In comments, compare this fence-based pattern with the
    //       acquire-release on the flag directly.
}

int main() {
    std::cout << "=== 14: Atomics & Memory Model ===\n\n";

    std::cout << "-- Atomic counter --\n";      demo_atomic_counter();
    std::cout << "\n-- Spinlock --\n";            demo_spinlock();
    std::cout << "\n-- Acquire-Release --\n";     demo_acquire_release();
    std::cout << "\n-- CAS --\n";                 demo_cas();
    std::cout << "\n-- Memory fence --\n";        demo_fence();

    return 0;
}
