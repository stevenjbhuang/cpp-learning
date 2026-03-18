cmake_minimum_required(VERSION 3.25)
project(CppLearning LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(
        -Wall -Wextra -Wpedantic
        -Wno-unused-parameter
        -fcolor-diagnostics
    )
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -O0 -fsanitize=address,undefined)
        add_link_options(-fsanitize=address,undefined)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-O2)
    endif()
endif()

find_package(Threads REQUIRED)
find_package(TBB QUIET)

# ── Tier 1: Basics (C++17) ───────────────────────────────────────────────────
add_subdirectory(01_fundamentals)
add_subdirectory(02_functions_and_scope)
add_subdirectory(03_pointers_and_references)
add_subdirectory(04_oop_basics)
add_subdirectory(05_operator_overloading)
add_subdirectory(06_stl_containers)
add_subdirectory(07_stl_algorithms)
add_subdirectory(08_templates_basics)
add_subdirectory(09_error_handling)

# ── Tier 2: Intermediate (C++17/20) ──────────────────────────────────────────
add_subdirectory(10_move_semantics)
add_subdirectory(11_smart_pointers)
add_subdirectory(12_lambdas_functionals)
add_subdirectory(13_concurrency_basics)
add_subdirectory(14_atomic_memory_model)
add_subdirectory(15_advanced_templates)
add_subdirectory(16_concepts_cpp20)
add_subdirectory(17_ranges_cpp20)
add_subdirectory(18_coroutines_cpp20)
add_subdirectory(19_data_structures)

# ── Tier 3: Advanced (C++20/23) ──────────────────────────────────────────────
add_subdirectory(20_lock_free_programming)
add_subdirectory(21_memory_and_allocators)
add_subdirectory(22_cache_optimization)
add_subdirectory(23_parallel_algorithms)
add_subdirectory(24_cpp23_features)
add_subdirectory(25_advanced_coroutines)
add_subdirectory(26_simd_vectorization)
add_subdirectory(27_low_latency_patterns)
add_subdirectory(28_robotics_patterns)
