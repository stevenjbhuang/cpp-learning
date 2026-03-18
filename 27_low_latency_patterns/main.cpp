/*
 * ============================================================
 * Module 27 — Low-Latency Patterns (C++17)
 * ============================================================
 *
 * Low-latency systems must respond to events in microseconds
 * or nanoseconds. Standard library abstractions are often too
 * expensive; instead we use lock-free queues, busy-wait loops,
 * CPU affinity, and careful memory layout.
 *
 * This module is a survey of patterns used in HFT, real-time
 * audio, robotics control loops, and network packet processing.
 *
 * Key concepts:
 *
 * 1. Busy-wait (spin loop)
 *    - `while (!ready.load(acquire));` — burns CPU but reacts in nanoseconds
 *    - Use pause / _mm_pause() to reduce power and bus contention
 *    - Only appropriate when the wait is expected to be very short
 *    - Requires a dedicated CPU core (set affinity + isolcpus)
 *
 * 2. CPU affinity
 *    - Pin a thread to a specific core: pthread_setaffinity_np (Linux)
 *    - Reduces context-switch overhead and cache invalidation
 *    - Combine with isolcpus kernel parameter for real-time workloads
 *    - sched_setscheduler(SCHED_FIFO) for real-time priority
 *
 * 3. Huge pages
 *    - Default page size: 4 KB; huge pages: 2 MB or 1 GB
 *    - Fewer TLB entries needed → less TLB pressure on hot data
 *    - mmap(MAP_HUGETLB) or /proc/sys/vm/nr_hugepages
 *    - Linux transparent huge pages (THP): auto-promoted but unpredictable
 *
 * 4. Branch elimination & branchless code
 *    - See Module 22; revisited here for real-time contexts
 *    - Use bitmasks, conditional moves, and table lookups
 *    - Avoid virtual calls on the critical path; use function pointers or CRTP
 *
 * 5. Latency measurement
 *    - RDTSC: read CPU timestamp counter — nanosecond resolution, no syscall
 *    - std::chrono::high_resolution_clock on Linux wraps CLOCK_MONOTONIC
 *    - Percentile latency: P50, P99, P99.9 are more meaningful than average
 *    - Avoid std::cout in the hot path — it flushes and is slow
 *
 * 6. Memory pre-allocation & no-malloc guarantees
 *    - mlockall(MCL_CURRENT | MCL_FUTURE): prevents page faults at runtime
 *    - Pre-fault pages by writing to them at startup
 *    - Use object pools (Module 21) — no new/delete on the critical path
 *    - Avoid std::string in hot paths — it may allocate; use string_view
 *
 * 7. Lock-free SPSC queue on the critical path
 *    - See Module 20; used here in a realistic pipeline
 *    - Producer (sensor thread) → queue → Consumer (control thread)
 *
 * Build & run (uses -march=native -O3):
 *   make run MODULE=27_low_latency_patterns
 * ============================================================
 */

#include <atomic>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>
#include <vector>

#if defined(__x86_64__)
#    include <immintrin.h>  // _mm_pause
#    define CPU_RELAX() _mm_pause()
#else
#    define CPU_RELAX() std::this_thread::yield()
#endif

using Clock = std::chrono::high_resolution_clock;
using ns    = std::chrono::nanoseconds;

// ── 1. Latency histogram ─────────────────────────────────────────────────────
// TODO: Implement class LatencyHistogram:
//   - Records nanosecond samples in logarithmic buckets
//   - void record(uint64_t ns)
//   - void print() const  — prints P50, P90, P99, P99.9, max
//   Simpler alternative: just collect into a sorted vector and compute percentiles.

// ── 2. Spin-wait with pause ───────────────────────────────────────────────────
// TODO: Implement `template <typename Pred> void spin_until(Pred pred)`:
//   while (!pred()) { CPU_RELAX(); }
//   Time how long it takes to detect a flag set by another thread.
//   Record samples in LatencyHistogram.

void demo_busy_wait() {
    std::atomic<bool> ready{false};

    // TODO: Spawn a producer thread that sleeps ~1 µs then sets ready = true.
    // TODO: Consumer: spin_until([&]{ return ready.load(acquire); });
    //       Measure the latency from set to detect using RDTSC or high_res_clock.
    //       Repeat 10000 times and print the histogram.
}

// ── 3. RDTSC timer ────────────────────────────────────────────────────────────
#if defined(__x86_64__)
// TODO: Implement `inline uint64_t rdtsc()` using __rdtsc() or inline asm.
//       Print the frequency calibration: measure rdtsc ticks per std::chrono ns.
#endif

// ── 4. Branchless absolute value and clamp ───────────────────────────────────
// TODO: Implement `int branchless_abs(int x)` without an if statement:
//   int mask = x >> 31;          // arithmetic right shift: all 1s if negative
//   return (x ^ mask) - mask;
//
// TODO: Implement `int branchless_clamp(int x, int lo, int hi)`.
//
// TODO: Benchmark branchless vs std::abs/std::clamp on 1M values. Print speedup.

// ── 5. Hot/cold path separation ───────────────────────────────────────────────
// TODO: Implement a function that has a rare error path:
//
//   [[gnu::hot]] inline int fast_process(int x) {
//       if (__builtin_expect(x < 0, 0)) return handle_error(x);  // cold
//       return x * x;  // hot
//   }
//
//   [[gnu::cold]] int handle_error(int x) {
//       std::cerr << "error: " << x << "\n";
//       return -1;
//   }
//
// TODO: Alternatively use C++20 [[likely]] / [[unlikely]].
// TODO: Comment on how the compiler lays out code differently for hot/cold hints.

// ── 6. Sensor → control pipeline ─────────────────────────────────────────────
// TODO: Implement a minimal real-time pipeline using the SPSC queue from Module 20:
//
//   struct SensorFrame { double value; uint64_t timestamp_ns; };
//
//   Sensor thread: every 1ms, push a SensorFrame onto the SPSC queue.
//   Control thread: busy-spin on the queue, consume frames, compute latency
//     (current_time - frame.timestamp_ns), record in histogram.
//
//   Run for 1 second, then print the latency histogram.

int main() {
    std::cout << "=== 27: Low-Latency Patterns ===\n\n";

    std::cout << "-- Busy wait latency --\n";
    demo_busy_wait();

    std::cout << "\n-- Branchless --\n";
    // TODO: Print branchless_abs(-42), branchless_clamp(15, 0, 10).
    // TODO: Run benchmark.

    std::cout << "\n-- Hot/cold path --\n";
    // TODO: Call fast_process(4) and fast_process(-1).

    std::cout << "\n-- Sensor pipeline --\n";
    // TODO: Run the sensor→control pipeline and print histogram.

    return 0;
}
