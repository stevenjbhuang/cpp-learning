/*
 * ============================================================
 * Module 26 — SIMD & Vectorization (C++17 / platform intrinsics)
 * ============================================================
 *
 * SIMD (Single Instruction, Multiple Data) allows one CPU
 * instruction to operate on multiple data elements simultaneously.
 * Modern processors can process 8 floats or 4 doubles in a single
 * cycle using AVX2 — a potential 8× throughput improvement over
 * scalar code.
 *
 * Key concepts:
 *
 * 1. Auto-vectorization
 *    - The compiler converts scalar loops to SIMD automatically
 *    - Requirements: no loop-carried dependencies, contiguous access,
 *      no aliasing (use __restrict__ or -fno-strict-aliasing carefully)
 *    - Flags: -O2 or higher, -march=native, -fvectorize
 *    - Inspect: -Rpass=loop-vectorize (Clang) or -fopt-info-vec (GCC)
 *    - Use std::assume_aligned<N>(ptr) to tell the compiler about alignment
 *
 * 2. x86 SSE / AVX intrinsics
 *    - Include <immintrin.h> for all x86 SIMD intrinsics
 *    - Register types: __m128 (4×float), __m128d (2×double),
 *                      __m256 (8×float), __m256d (4×double)
 *    - Load: _mm256_load_ps (aligned), _mm256_loadu_ps (unaligned)
 *    - Store: _mm256_store_ps, _mm256_storeu_ps
 *    - Arithmetic: _mm256_add_ps, _mm256_mul_ps, _mm256_fmadd_ps (FMA)
 *    - Horizontal sum: requires manual shuffles (hadd pattern)
 *    - Prefer aligned buffers: alignas(32) float buf[8];
 *
 * 3. std::experimental::simd (C++ parallel TS / draft C++26)
 *    - Portable SIMD abstraction; avoids platform-specific intrinsics
 *    - Not yet standard; check compiler support before using
 *    - Alternative: highway, xsimd, or eve — production-quality portable SIMD
 *
 * 4. Gather / scatter
 *    - Gather: load from non-contiguous indices (_mm256_i32gather_ps)
 *    - Scatter: store to non-contiguous indices (AVX-512 or emulate)
 *    - Much slower than contiguous load/store — avoid in inner loops
 *
 * 5. Measuring vectorization
 *    - Check assembly: godbolt.org or `objdump -d`; look for ymm/xmm registers
 *    - Benchmark with std::chrono; compute GB/s or GFLOP/s
 *    - Compare scalar, auto-vectorized, and intrinsic versions
 *
 * Build & run (uses -march=native -O3 -fvectorize):
 *   make run MODULE=26_simd_vectorization
 * ============================================================
 */

#include <chrono>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>

#if defined(__AVX2__)
#    include <immintrin.h>
#    define HAS_AVX2 1
#endif

using Clock = std::chrono::high_resolution_clock;
constexpr std::size_t N = 1 << 24;  // 16M elements

// ── 1. Auto-vectorization ─────────────────────────────────────────────────────
// TODO: Implement `void add_arrays_scalar(const float* a, const float* b, float* c, int n)`.
//       Simple loop: c[i] = a[i] + b[i].
//
// TODO: Implement `void add_arrays_auto(const float* __restrict__ a,
//                                       const float* __restrict__ b,
//                                       float* __restrict__ c, int n)`.
//       Same loop but with __restrict__ — allows auto-vectorization.
//
// TODO: Compile both with -O2 and inspect the assembly. The auto version
//       should use xmm/ymm registers. Comment on what you observe.

// ── 2. AVX2 intrinsics — manual vectorized add ────────────────────────────────
#ifdef HAS_AVX2
// TODO: Implement `void add_arrays_avx2(const float* a, const float* b, float* c, int n)`:
//   Process 8 floats per iteration with _mm256_loadu_ps / _mm256_add_ps / _mm256_storeu_ps.
//   Handle the tail (n % 8 remaining elements) with scalar code.
#endif

// ── 3. AVX2 — dot product with FMA ────────────────────────────────────────────
#ifdef HAS_AVX2
// TODO: Implement `float dot_product_avx2(const float* a, const float* b, int n)`:
//   - Accumulate in __m256 acc = _mm256_setzero_ps()
//   - Use _mm256_fmadd_ps(va, vb, acc) — fused multiply-add
//   - Reduce acc to scalar: horizontal add using _mm256_hadd_ps pattern
//
// HINT for horizontal reduction:
//   __m128 lo = _mm256_castps256_ps128(acc);
//   __m128 hi = _mm256_extractf128_ps(acc, 1);
//   __m128 sum = _mm_add_ps(lo, hi);
//   sum = _mm_hadd_ps(sum, sum);
//   sum = _mm_hadd_ps(sum, sum);
//   return _mm_cvtss_f32(sum);
#endif

// ── 4. Alignment helper ───────────────────────────────────────────────────────
// TODO: Write a helper that allocates N floats aligned to 32 bytes:
//   std::vector with custom allocator, or aligned_alloc.
//   Verify the address is divisible by 32.

// ── 5. Benchmark ─────────────────────────────────────────────────────────────
void benchmark() {
    // TODO: Allocate aligned arrays a[N], b[N], c[N].
    //       Fill a and b with 1.0f.
    //
    // TODO: Time add_arrays_scalar(a, b, c, N). Compute GB/s.
    // TODO: Time add_arrays_auto(a, b, c, N). Compute GB/s.
    //
    // #ifdef HAS_AVX2
    // TODO: Time add_arrays_avx2(a, b, c, N). Compute GB/s.
    // TODO: Time dot_product_avx2(a, b, N). Compute GFLOP/s.
    // #endif
    //
    // TODO: Print a table: version | time (ms) | GB/s | speedup.
}

// ── 6. Portable SIMD hint — std::assume_aligned ───────────────────────────────
void demo_assume_aligned() {
    // TODO: Allocate a 32-byte-aligned float array.
    //       Use `auto* p = std::assume_aligned<32>(raw_ptr)` to tell the compiler.
    //       Show in comments that the assembly changes (no alignment check).
}

int main() {
    std::cout << "=== 26: SIMD Vectorization ===\n\n";

#ifdef HAS_AVX2
    std::cout << "AVX2 available\n\n";
#else
    std::cout << "AVX2 not available — only scalar/auto-vec demos will run\n\n";
#endif

    benchmark();
    demo_assume_aligned();

    return 0;
}
