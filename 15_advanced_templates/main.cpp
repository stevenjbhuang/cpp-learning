/*
 * ============================================================
 * Module 15 — Advanced Templates (C++17)
 * ============================================================
 *
 * Advanced template techniques enable zero-cost abstractions,
 * policy-based design, and compile-time computation that rivals
 * hand-written special-case code. This module covers patterns
 * that appear throughout high-performance C++ libraries.
 *
 * Key concepts:
 *
 * 1. Curiously Recurring Template Pattern (CRTP)
 *    - `template <typename Derived> class Base { ... }`
 *    - Derived inherits from Base<Derived>
 *    - Enables static (compile-time) polymorphism — no vtable overhead
 *    - Common uses: mixins, counting instances, operator generation
 *    - C++23 "deducing this" is a cleaner alternative for some CRTP uses
 *
 * 2. Policy-based design
 *    - Parameterise a class with strategy types (policies)
 *    - Policies are injected as template parameters (not virtual functions)
 *    - Zero overhead: no virtual dispatch, inlinable
 *    - Example: Allocator policy in STL containers
 *
 * 3. Expression templates
 *    - Represent lazy arithmetic expressions as types
 *    - Evaluate the full expression in a single pass — avoids temporaries
 *    - Foundation of Eigen, Blaze, and other linear algebra libraries
 *
 * 4. Template metaprogramming (TMP)
 *    - Computations at compile time using recursive template instantiation
 *    - Type lists: manipulating sequences of types at compile time
 *    - std::tuple, std::variant as standard type lists
 *    - std::integer_sequence / std::index_sequence for indexing packs
 *
 * 5. Variable templates (C++14)
 *    - template <typename T> constexpr bool is_fast_v = ...;
 *    - Cleaner than ::value accessor on traits
 *
 * 6. Template template parameters
 *    - A template parameter that is itself a template
 *    - `template <template <typename> class Container, typename T>`
 *    - Useful for adapting container types generically
 *
 * Build & run:
 *   make run MODULE=15_advanced_templates
 * ============================================================
 */

#include <array>
#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

// ── 1. CRTP — static polymorphism ────────────────────────────────────────────
// TODO: Implement a CRTP base `Printable<Derived>` that provides:
//   - void print() const — calls static_cast<const Derived*>(this)->to_string()
//   So any class deriving from Printable<T> just needs to implement to_string().
//
// TODO: Implement `struct Point : Printable<Point>`:
//   double x, y;
//   std::string to_string() const  — returns "(x, y)"
//
// TODO: Implement a CRTP mixin `Comparable<Derived>` that generates !=, >, <=, >=
//       from a derived class that provides `operator==` and `operator<`.

// ── 2. Policy-based Logger ────────────────────────────────────────────────────
// TODO: Implement policies:
//   struct ConsoleOutput { static void write(const std::string& s); }  — prints to cout
//   struct NullOutput    { static void write(const std::string& s); }  — no-op
//
// TODO: Implement `template <typename OutputPolicy> class Logger`:
//   - void log(const std::string& msg)  — calls OutputPolicy::write(...)
//   - uint32_t message_count() const
//
// TODO: In main, instantiate Logger<ConsoleOutput> and Logger<NullOutput>.
//       Show that NullOutput adds zero runtime cost (can be optimised away).

// ── 3. Compile-time type list ─────────────────────────────────────────────────
// TODO: Use std::index_sequence to implement:
//   template <typename Tuple, typename Func>
//   void for_each_in_tuple(Tuple&& t, Func&& f)
//
// HINT: Use std::make_index_sequence<std::tuple_size_v<Tuple>>{}
//       and a fold or pack expansion over std::get<Is>(t).

void demo_tuple_iteration() {
    auto t = std::make_tuple(42, 3.14, std::string("hello"));
    // TODO: Call for_each_in_tuple(t, [](const auto& v){ std::cout << v << "\n"; });
}

// ── 4. Expression template (minimal) ─────────────────────────────────────────
// TODO: Implement a minimal vector addition expression template:
//
//   struct Vec { std::array<double,3> data; };
//
//   template <typename L, typename R>
//   struct AddExpr {
//       const L& lhs; const R& rhs;
//       double operator[](std::size_t i) const { return lhs[i] + rhs[i]; }
//   };
//
//   AddExpr<L,R> operator+(const L& l, const R& r) { return {l, r}; }
//
//   // Evaluate into a Vec:
//   Vec eval(const auto& expr) — copies via subscript
//
// HINT: The key insight: `a + b + c` creates AddExpr<AddExpr<Vec,Vec>,Vec>
//       and evaluates each element once with no temporary Vec created.

// ── 5. Variable template ──────────────────────────────────────────────────────
// TODO: Define `template <typename T> inline constexpr bool is_numeric_v`
//       that is true for integral and floating-point types.
//       Use it in a template function that prints "numeric" or "non-numeric".

// ── 6. Template template parameter ────────────────────────────────────────────
// TODO: Implement `template <template <typename,typename> class Container, typename T>`
//       void fill_and_print(Container<T, std::allocator<T>>& c, std::initializer_list<T> items)
//       that inserts items into c and prints them.
//       Call it with both std::vector<int> and std::list<int>.

int main() {
    std::cout << "=== 15: Advanced Templates ===\n\n";

    std::cout << "-- CRTP --\n";
    // TODO: Create Point{1.0, 2.0}. Call point.print().
    // TODO: Demonstrate Comparable: create two Points, test !=, >, <=.

    std::cout << "\n-- Policy Logger --\n";
    // TODO: Log 3 messages with ConsoleOutput logger, 3 with NullOutput.

    std::cout << "\n-- Tuple iteration --\n";
    demo_tuple_iteration();

    std::cout << "\n-- Expression templates --\n";
    // TODO: Create three Vecs, add them, eval the result, print elements.

    std::cout << "\n-- Variable template --\n";
    // TODO: Test is_numeric_v<int>, is_numeric_v<double>, is_numeric_v<std::string>.

    std::cout << "\n-- Template template --\n";
    // TODO: Call fill_and_print with vector and list.

    return 0;
}
