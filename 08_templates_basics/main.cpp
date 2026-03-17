/*
 * ============================================================
 * Module 08 — Templates Basics (C++17)
 * ============================================================
 *
 * Templates enable generic programming: writing code that works
 * with any type satisfying implicit (C++17) or explicit (C++20)
 * constraints. They are zero-cost abstractions — all instantiation
 * happens at compile time with no runtime overhead.
 *
 * Key concepts:
 *
 * 1. Function templates
 *    - Syntax: template <typename T> T max(T a, T b)
 *    - Template argument deduction: compiler infers T from arguments
 *    - Explicit instantiation: max<double>(1, 2.0)
 *    - Function template overloading and specialisation
 *
 * 2. Class templates
 *    - Parameterise the entire class on one or more types
 *    - Member functions defined outside the class need the template header
 *    - Non-type template parameters: template <typename T, std::size_t N>
 *
 * 3. Template specialisation
 *    - Full specialisation: override for a specific type
 *    - Partial specialisation (class templates only): override for a family of types
 *    - Primary template + specialisations follow the most-specialised-wins rule
 *
 * 4. Variadic templates (C++11+)
 *    - template <typename... Ts> — zero or more type parameters
 *    - Parameter pack expansion: Ts... in function parameters
 *    - Recursion or fold expressions (C++17) to process each element
 *
 * 5. Fold expressions (C++17)
 *    - Compact syntax to apply a binary operator across a pack:
 *        (args + ...)     — left fold
 *        (... + args)     — right fold
 *        (init + ... + args) — binary fold with initial value
 *
 * 6. if constexpr (C++17)
 *    - Compile-time branch selection inside a template
 *    - The discarded branch is not instantiated — enables type-based dispatch
 *    - Use instead of SFINAE for readable type-dispatch
 *
 * 7. SFINAE basics (Substitution Failure Is Not An Error)
 *    - std::enable_if<condition, T>::type — remove function from overload set
 *    - std::is_integral_v<T>, std::is_floating_point_v<T>, std::is_same_v<T,U>
 *    - Largely superseded by Concepts (Module 16) in C++20
 *
 * Build & run:
 *   make run MODULE=08_templates_basics
 * ============================================================
 */

#include <array>
#include <iostream>
#include <string>
#include <type_traits>

// ── 1. Function templates ─────────────────────────────────────────────────────
// TODO: Implement `template <typename T> T my_max(T a, T b)`.
//       Call it with ints, doubles, and strings. Let the compiler deduce T.

// TODO: Implement `template <typename T> void print_type(const T& val)`
//       that prints the value and — using if constexpr — prints "integral",
//       "floating-point", or "other" based on the type trait.

// ── 2. Class template ─────────────────────────────────────────────────────────
// TODO: Implement `template <typename T, std::size_t N> class StaticStack`:
//   - Backed by std::array<T, N>
//   - void push(const T& val)  — assert or throw on overflow
//   - T pop()                  — assert or throw on underflow
//   - const T& top() const
//   - bool empty() const
//   - std::size_t size() const

// ── 3. Template specialisation ───────────────────────────────────────────────
// TODO: Write a primary template `template <typename T> struct Serialise`
//       with a static method `std::string to_string(const T& v)` that calls
//       std::to_string(v).
//
// TODO: Specialise it for std::string: just return the string as-is.
//
// TODO: Specialise it for bool: return "true" or "false" instead of "1"/"0".

// ── 4. Variadic templates + fold expressions ──────────────────────────────────
// TODO: Implement `template <typename... Ts> auto sum(Ts... args)` using a
//       fold expression. Call it with 3 ints, then a mix of int and double.

// TODO: Implement `template <typename... Ts> void print_all(Ts... args)` that
//       prints each argument separated by ", " using fold + operator<<.

// ── 5. SFINAE with std::enable_if ────────────────────────────────────────────
// TODO: Write an overloaded `describe()` function:
//   - One overload enabled only for integral types (std::is_integral_v)
//     → prints "integral: <value>"
//   - One overload enabled only for floating-point types
//     → prints "float: <value>"
//   Use std::enable_if_t<condition, int> = 0 as a defaulted non-type parameter.

int main() {
    std::cout << "=== 08: Templates Basics ===\n\n";

    std::cout << "-- Function templates --\n";
    // TODO: Test my_max with int, double, string.
    // TODO: Test print_type with int, double, std::string.

    std::cout << "\n-- Class template: StaticStack --\n";
    // TODO: Create StaticStack<int, 8>, push 1..5, pop twice, print top.

    std::cout << "\n-- Specialisation --\n";
    // TODO: Serialise<int>::to_string(42), Serialise<std::string>::to_string("hi"),
    //       Serialise<bool>::to_string(true). Print all.

    std::cout << "\n-- Variadic / fold --\n";
    // TODO: Print sum(1, 2, 3, 4, 5).
    // TODO: Print sum(1, 2.5, 3).
    // TODO: Call print_all(1, "hello", 3.14, true).

    std::cout << "\n-- SFINAE --\n";
    // TODO: Call describe(42), describe(3.14).

    return 0;
}
