add_executable(26_simd_vectorization main.cpp)
target_compile_options(26_simd_vectorization PRIVATE -march=native -O3 -fvectorize -fslp-vectorize)
