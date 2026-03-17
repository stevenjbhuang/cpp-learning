/*
 * ============================================================
 * Module 23 — Parallel Algorithms (C++17)
 * ============================================================
 *
 * C++17 added execution policies to STL algorithms, enabling
 * data-parallel processing with a single keyword change.
 * On systems with TBB or a compatible runtime, the work is
 * automatically distributed across all hardware threads.
 *
 * Key concepts:
 *
 * 1. Execution policies (<execution>)
 *    - std::execution::seq          — sequential, deterministic
 *    - std::execution::par          — parallel, unspecified thread order
 *    - std::execution::par_unseq    — parallel + SIMD (no synchronisation in loop body)
 *    - std::execution::unseq (C++20) — SIMD on a single thread
 *
 * 2. Parallel algorithms
 *    - Nearly all <algorithm> and <numeric> algorithms accept a policy
 *    - std::transform(par, ...)
 *    - std::reduce(par, ...)         — parallel reduce (associative ops)
 *    - std::transform_reduce(par, ...) — parallel map-reduce
 *    - std::for_each(par, ...)
 *    - std::sort(par, ...)
 *    - std::inclusive_scan / exclusive_scan (par)
 *
 * 3. Requirements & pitfalls
 *    - The callable must be safe to call from multiple threads
 *    - No shared mutable state without synchronisation in par_unseq
 *    - std::reduce is NOT std::accumulate: order of operations is unspecified,
 *      so the operation must be associative and commutative
 *    - Exceptions: if the callable throws with par, std::terminate is called
 *
 * 4. std::reduce vs std::accumulate
 *    - accumulate: left fold, sequential, any binary op
 *    - reduce: associative fold, can be parallel, init value required
 *    - For floating-point: parallel reduce may give slightly different results
 *      due to non-associativity of floating-point addition
 *
 * 5. Custom parallel patterns
 *    - Parallel prefix sum (scan): std::inclusive_scan(par, ...)
 *    - Parallel partition: std::partition(par, ...)
 *    - Parallel copy_if (filter): std::copy_if(par, ...)
 *
 * 6. Work stealing & thread pool
 *    - TBB's scheduler uses work-stealing: idle threads steal tasks from busy ones
 *    - Fine-grained tasks benefit most; coarse tasks may have insufficient parallelism
 *    - Amdahl's law: speedup limited by the sequential fraction
 *
 * Build & run (links TBB if available):
 *   make run MODULE=23_parallel_algorithms
 * ============================================================
 */

#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#ifdef HAS_TBB
#    include <tbb/tbb.h>
#endif

using Clock = std::chrono::high_resolution_clock;

// ── 1. std::sort — seq vs par ─────────────────────────────────────────────────
void bench_parallel_sort() {
    // TODO: Generate a vector of 10M random ints using std::mt19937.
    // TODO: Make two copies.
    // TODO: Time std::sort(seq, ...) on one copy.
    // TODO: Time std::sort(par, ...) on the other.
    // TODO: Print elapsed times and speedup.
    //       Verify both produce the same sorted order.
}

// ── 2. std::transform — element-wise sqrt ────────────────────────────────────
void bench_parallel_transform() {
    // TODO: Create vector<double> of 20M elements (values 1.0..20M).
    // TODO: std::transform(seq, ...) sqrt into output_seq.
    // TODO: std::transform(par, ...) sqrt into output_par.
    // TODO: Verify results are identical (element-wise), print speedup.
}

// ── 3. std::reduce — parallel sum ────────────────────────────────────────────
void bench_parallel_reduce() {
    std::vector<double> v(1 << 24);  // 16M elements
    std::iota(v.begin(), v.end(), 1.0);

    // TODO: Time std::accumulate(v, 0.0)  — sequential.
    // TODO: Time std::reduce(seq, v, 0.0) — sequential reduce.
    // TODO: Time std::reduce(par, v, 0.0) — parallel reduce.
    // TODO: Print results — note the slight floating-point difference for par.
    //       Explain in a comment why the results may differ.
}

// ── 4. std::transform_reduce — dot product ────────────────────────────────────
void bench_transform_reduce() {
    std::size_t N = 1 << 22;  // 4M elements
    std::vector<float> a(N, 1.0f), b(N, 2.0f);

    // TODO: Compute dot product a·b with std::transform_reduce(seq, ...):
    //   std::transform_reduce(seq, a.begin(), a.end(), b.begin(), 0.0f)
    // TODO: Repeat with par and par_unseq policies.
    // TODO: Print results (expected: N * 2.0) and speedup over seq.
}

// ── 5. Parallel prefix scan ───────────────────────────────────────────────────
void bench_parallel_scan() {
    std::vector<int> v(1 << 20);
    std::iota(v.begin(), v.end(), 1);

    // TODO: std::inclusive_scan(seq, v, out_seq)
    // TODO: std::inclusive_scan(par, v, out_par)
    // TODO: Verify last elements of both match. Print time ratio.
}

int main() {
    std::cout << "=== 23: Parallel Algorithms ===\n\n";

    std::cout << "-- Parallel sort --\n";           bench_parallel_sort();
    std::cout << "\n-- Parallel transform --\n";    bench_parallel_transform();
    std::cout << "\n-- Parallel reduce --\n";       bench_parallel_reduce();
    std::cout << "\n-- transform_reduce (dot) --\n"; bench_transform_reduce();
    std::cout << "\n-- Parallel scan --\n";         bench_parallel_scan();

#ifdef HAS_TBB
    std::cout << "\n-- TBB available: "
              << tbb::info::default_concurrency() << " threads --\n";
#endif

    return 0;
}
