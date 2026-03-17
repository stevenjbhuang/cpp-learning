add_executable(18_coroutines_cpp20 main.cpp)
# Coroutines are standard in C++20; no extra flags needed with Clang 17+.
# If using an older toolchain, add: target_compile_options(18_coroutines_cpp20 PRIVATE -fcoroutines)
