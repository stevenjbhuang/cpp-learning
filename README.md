# C++ Learning Path — C++17 → C++20 → C++23

A structured, hands-on curriculum for mastering modern C++ with a focus on
**low-latency programming**, **concurrent systems**, and **robotics**.
Each module is a self-contained, buildable program demonstrating a cohesive set of concepts.

---

## Prerequisites

| Tool | Minimum Version | Notes |
|------|----------------|-------|
| Clang / Clang++ | 17+ | Primary compiler; C++23 support |
| CMake | 3.25+ | Build system generator |
| Ninja | 1.11+ | Build backend |
| clang-format | 17+ | Code formatting |
| clang-tidy | 17+ | Static analysis |
| TBB (optional) | 2021+ | Required for `23_parallel_algorithms` |

Install on Ubuntu/Debian:
```bash
sudo apt install clang ninja-build cmake clang-format clang-tidy libtbb-dev
```

---

## Quick Start

```bash
# Build all modules
make build

# Run a specific module
make run MODULE=01_fundamentals

# Build with sanitizers (Debug)
make build-debug && make run MODULE=13_concurrency_basics

# Format all source files
make format

# Static analysis
make tidy
```

---

## Project Structure

```
cpp-learning/
├── CMakeLists.txt          # Root build configuration
├── Makefile                # Convenience targets
├── .clang-format           # Formatting rules
├── .clangd                 # Language server configuration
│
├── 01_fundamentals/        # Tier 1 — Basics
│   ├── CMakeLists.txt
│   └── main.cpp
├── 02_functions_and_scope/
│   └── ...
│   ...
├── 10_move_semantics/      # Tier 2 — Intermediate
│   └── ...
│   ...
└── 20_lock_free_programming/ # Tier 3 — Advanced
    └── ...
```

---

## Learning Path

### Tier 1 — Basics (C++17)

| Module | Concepts |
|--------|----------|
| **01 Fundamentals** | Primitive types, `auto`, structured bindings, range-for, `if`/`switch` initializers, `std::string`, `std::array` |
| **02 Functions & Scope** | Overloading, default args, `constexpr`, `inline`, namespaces, ADL, `std::string_view` |
| **03 Pointers & References** | Raw pointers, pointer arithmetic, references, `const` correctness, `nullptr`, `std::span` |
| **04 OOP Basics** | Classes, constructors/destructors, inheritance, virtual dispatch, `override`/`final`, abstract classes |
| **05 Operator Overloading** | Arithmetic, comparison, stream I/O, subscript, call operator, spaceship `<=>` |
| **06 STL Containers** | `vector`, `deque`, `list`, `map`, `unordered_map`, `set`, `array`, `stack`, `queue` |
| **07 STL Algorithms** | `sort`, `find_if`, `transform`, `accumulate`, `partition`, `copy_if`, `for_each` |
| **08 Templates Basics** | Function/class templates, specialization, CTAD, non-type template parameters |
| **09 Error Handling** | Exceptions, `noexcept`, `std::optional`, `std::variant`, `std::any` |

### Tier 2 — Intermediate (C++17 / C++20)

| Module | Concepts |
|--------|----------|
| **10 Move Semantics** | lvalue/rvalue, move ctor/assignment, `std::move`, `std::forward`, perfect forwarding, RVO/NRVO |
| **11 Smart Pointers** | `unique_ptr`, `shared_ptr`, `weak_ptr`, custom deleters, cyclic reference pitfalls |
| **12 Lambdas & Functionals** | Captures, generic lambdas, `std::function`, recursive lambdas, `std::bind` |
| **13 Concurrency Basics** | `std::thread`, `mutex`, `condition_variable`, `async`/`future`/`promise`, thread pool sketch |
| **14 Atomic & Memory Model** | `std::atomic`, memory orders, `compare_exchange`, lock-free counter, `std::atomic_ref` |
| **15 Advanced Templates** | Variadic templates, fold expressions, `if constexpr`, SFINAE, `enable_if`, type traits |
| **16 Concepts (C++20)** | `concept`, `requires` expressions, constrained templates, standard concept library |
| **17 Ranges (C++20)** | `std::ranges` algorithms, views, pipelines (`filter | transform | take`), lazy evaluation |
| **18 Coroutines (C++20)** | `co_yield`, `co_await`, `co_return`, generator, simple async task, promise type |
| **19 Data Structures** | Ring buffer, intrusive list, sorted-vector map, SOA vs AOS, sparse arrays |

### Tier 3 — Advanced (C++20 / C++23)

| Module | Concepts |
|--------|----------|
| **20 Lock-Free Programming** | Lock-free stack/queue (CAS), ABA problem, epoch-based reclamation, hazard pointers |
| **21 Memory & Allocators** | `std::pmr`, pool allocator, monotonic/arena allocator, custom STL allocator |
| **22 Cache Optimization** | Cache line size, false sharing, data-oriented design, struct padding, `__builtin_prefetch` |
| **23 Parallel Algorithms** | `std::execution::par`/`par_unseq`, parallel STL, `transform_reduce`, work-stealing |
| **24 C++23 Features** | `std::expected`, `std::flat_map`/`flat_set`, `std::mdspan`, `std::print`, deducing `this` |
| **25 Advanced Coroutines** | Task scheduler, async generator, coroutine-based state machine, channel primitives |
| **26 SIMD & Vectorization** | Auto-vectorization, SSE/AVX intrinsics, alignment, vectorization-friendly layouts |
| **27 Low-Latency Patterns** | RDTSC timing, busy-wait, CPU affinity, branch prediction hints, huge pages, percentiles |
| **28 Robotics Patterns** | State machines, PID controller, fixed-timestep loop, sensor pipelines, event queues |

---

## Key Themes

### Concurrency & Thread Safety
- Thread lifecycle, detach vs join
- Mutual exclusion: `mutex`, `shared_mutex`, spinlocks
- Condition variables and semaphores (`std::counting_semaphore` C++20)
- Atomics and the C++ memory model (happens-before, synchronizes-with)
- Lock-free and wait-free algorithms
- Coroutines as cooperative concurrency primitives

### Low-Latency Techniques
- Avoiding dynamic allocation on the hot path (pool/arena allocators)
- Cache-friendly data layout (SoA, flat containers, padding)
- Minimizing branch mispredictions (`[[likely]]`/`[[unlikely]]`, branch-free arithmetic)
- SIMD vectorization for throughput
- Busy-polling vs interrupt-driven I/O
- CPU pinning and NUMA awareness

### Robotics Relevance
- Deterministic execution with fixed-rate control loops
- State machines for behavior modelling
- PID and feed-forward control
- Lock-free ring buffers for sensor data
- Event-driven sensor fusion pipelines
- Real-time-safe memory allocation

---

## C++ Standard Progression

```
C++17  ──▶  Modules 01–15  (structured bindings, if constexpr, std::optional/variant,
                             fold expressions, CTAD, std::string_view, std::filesystem)

C++20  ──▶  Modules 16–25  (concepts, ranges, coroutines, std::span, jthread,
                             counting_semaphore, std::format, three-way comparison)

C++23  ──▶  Module 24+     (std::expected, std::flat_map/set, std::mdspan,
                             std::print/println, deducing this, std::generator)
```

---

## Build System Notes

- **Generator**: Ninja (fast incremental builds)
- **Compiler**: Clang++ (best C++23 support, excellent diagnostics)
- **`compile_commands.json`** is exported to `build/` — clangd picks it up via `.clangd`
- Debug builds enable **AddressSanitizer** and **UndefinedBehaviorSanitizer**
- Each module compiles as a standalone executable: `build/<module>/<module>`
