/*
 * ============================================================
 * Module 22 — Cache Optimization (C++17)
 * ============================================================
 *
 * Modern CPUs are memory-bound, not compute-bound. Accessing
 * data that is already in cache (L1/L2/L3) can be 10–200× faster
 * than a main-memory access. Writing cache-friendly code is the
 * single most impactful performance technique for data-intensive
 * workloads.
 *
 * Key concepts:
 *
 * 1. Cache hierarchy
 *    - L1: ~4 cycles, 32–64 KB per core
 *    - L2: ~12 cycles, 256 KB–1 MB per core
 *    - L3: ~40 cycles, 8–64 MB shared
 *    - Main memory: ~200 cycles
 *    - Cache line: typically 64 bytes — the unit of transfer
 *
 * 2. Spatial locality
 *    - Access memory sequentially or in stride-1 patterns
 *    - Prefer flat arrays (vector, array) over pointer-chasing structures
 *    - Linked lists are cache-hostile; use them only for frequent mid-sequence edits
 *
 * 3. Temporal locality
 *    - Reuse data while it is still in cache
 *    - Loop tiling (blocking): process a tile that fits in cache before moving on
 *    - Fuse loops that access the same data
 *
 * 4. Array of Structs (AoS) vs Struct of Arrays (SoA)
 *    - AoS: struct { float x,y,z,w; } particles[N];
 *      → iterating only x loads unnecessary y,z,w into cache
 *    - SoA: struct { float x[N], y[N], z[N], w[N]; } particles;
 *      → iterating x is a contiguous stride-1 scan — ideal for SIMD
 *    - Use SoA when you process one field at a time (physics, ML inference)
 *    - Use AoS when you always need all fields together
 *
 * 5. False sharing
 *    - Two threads writing different variables on the same cache line
 *    - Use alignas(hardware_destructive_interference_size) to separate them
 *    - Covered in Module 20; benchmark here to see the impact
 *
 * 6. Prefetching
 *    - Hardware prefetcher detects sequential patterns automatically
 *    - Software prefetch: __builtin_prefetch(ptr, rw, locality)
 *    - Use sparingly — prefetching a cache line you will not use evicts useful data
 *
 * 7. Branch prediction
 *    - Modern CPUs speculatively execute predicted branches
 *    - Misprediction cost: ~15 cycles
 *    - [[likely]] / [[unlikely]] (C++20) hint to the compiler
 *    - Branchless alternatives: conditional moves (cmov), bitmask tricks
 *
 * Build & run (uses -march=native for accurate SIMD/cache results):
 *   make run MODULE=22_cache_optimization
 * ============================================================
 */

#include <chrono>
#include <cstddef>
#include <iostream>
#include <new>
#include <numeric>
#include <vector>

using Clock = std::chrono::high_resolution_clock;

// ── 1. Sequential vs random access ───────────────────────────────────────────
void bench_sequential_vs_random() {
    // TODO: Allocate a large vector<int> (e.g., 64 MB worth: 16M elements).
    // TODO: Time a sequential sum (stride 1) vs a random-index sum.
    //       For random, create a permuted index array.
    // TODO: Print the elapsed time for each and the speedup factor.
    //       Sequential should be ~5–20× faster.
}

// ── 2. AoS vs SoA ─────────────────────────────────────────────────────────────
constexpr std::size_t N = 1 << 20;  // 1M particles

// Array of Structs
struct ParticleAoS { float x, y, z, vx, vy, vz; };

// Struct of Arrays
struct ParticlesSoA {
    std::vector<float> x, y, z, vx, vy, vz;
    explicit ParticlesSoA(std::size_t n)
        : x(n), y(n), z(n), vx(n), vy(n), vz(n) {}
};

void bench_aos_vs_soa() {
    // TODO: Populate N AoS particles and N SoA particles with random floats.
    //
    // TODO: Benchmark "update only x positions": x[i] += vx[i] * dt
    //       - AoS version: for each particle, load 6 floats but use only 2
    //       - SoA version: x and vx are contiguous — stride-1, SIMD-friendly
    //
    // TODO: Print elapsed time for each and ratio.
    //       Expected: SoA is 2–4× faster for this access pattern.
}

// ── 3. Loop tiling (cache blocking) for matrix multiply ──────────────────────
// TODO: Implement two versions of N×N matrix multiplication:
//
//   void matmul_naive(const float* A, const float* B, float* C, int N)
//     — triple nested loop in i,j,k order
//
//   void matmul_tiled(const float* A, const float* B, float* C, int N, int tile)
//     — 6 nested loops with tile blocking; tile size = 32 or 64
//
// TODO: Time both on a 512×512 matrix. Print GFLOP/s for each.
// HINT: GFLOP/s = 2*N^3 / time_ns * 1e-9

// ── 4. Branch prediction & branchless code ────────────────────────────────────
void bench_branchy_vs_branchless() {
    // TODO: Fill a vector with random ints in [0,255].
    //
    // Branchy version:
    //   for (int v : data) if (v >= 128) sum += v;
    //
    // Branchless version:
    //   for (int v : data) sum += (v >= 128) * v;  // avoids branch
    //
    // TODO: Time both on 1M elements. The branchless version should be faster
    //       on unsorted data due to eliminated mispredictions.
    //
    // TODO: Sort the data and repeat — now the branchy version is predictable
    //       and may be equally fast. Explain in comments why.
}

int main() {
    std::cout << "=== 22: Cache Optimization ===\n\n";

    std::cout << "-- Sequential vs random --\n";
    bench_sequential_vs_random();

    std::cout << "\n-- AoS vs SoA --\n";
    bench_aos_vs_soa();

    std::cout << "\n-- Matrix multiply (naive vs tiled) --\n";
    // TODO: Run matmul benchmark.

    std::cout << "\n-- Branchy vs branchless --\n";
    bench_branchy_vs_branchless();

    return 0;
}
