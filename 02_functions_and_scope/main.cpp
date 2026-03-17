/*
 * ============================================================
 * Module 02 — Functions & Scope (C++17)
 * ============================================================
 *
 * This module covers how C++ manages functions, overloading,
 * compile-time evaluation, and name lookup rules.
 *
 * Key concepts:
 *
 * 1. Function overloading
 *    - Multiple functions with the same name, different parameter types
 *    - The compiler selects the best match via overload resolution
 *    - Pitfall: implicit conversions causing ambiguity
 *
 * 2. Default arguments
 *    - Must appear at the end of the parameter list
 *    - Declared in the function declaration (not definition if separate)
 *
 * 3. constexpr functions
 *    - Evaluated at compile time when all inputs are constant expressions
 *    - Can also run at runtime
 *    - Restrictions: no dynamic allocation, no virtual calls (pre-C++20)
 *    - Use `static_assert` to verify compile-time evaluation
 *
 * 4. [[nodiscard]] attribute
 *    - Compiler warning when the return value of a function is discarded
 *    - Useful for error codes, factory functions, expensive computations
 *
 * 5. Namespaces
 *    - Avoid name collisions; organise code into logical units
 *    - Nested namespaces: namespace a::b::c {} (C++17)
 *    - Inline namespaces for ABI versioning
 *    - Anonymous namespaces for translation-unit-local linkage
 *
 * 6. Argument-Dependent Lookup (ADL)
 *    - Unqualified function calls search namespaces of their argument types
 *    - This is how `operator<<` and `std::swap` customisation points work
 *
 * 7. std::string_view
 *    - Non-owning, read-only view over a string buffer
 *    - Zero-copy; safe to pass to functions instead of const std::string&
 *    - Danger: the underlying string must outlive the view
 *
 * 8. Inline variables (C++17)
 *    - ODR-safe constants defined in headers
 *    - Syntax: inline constexpr double pi = 3.14159...;
 *
 * Build & run:
 *   make run MODULE=02_functions_and_scope
 * ============================================================
 */

#include <cmath>
#include <iostream>
#include <string>
#include <string_view>

// ── 1. Function overloading ───────────────────────────────────────────────────
// TODO: Define three overloads of `print` that each accept a different type:
//         void print(int x)
//         void print(double x)
//         void print(std::string_view sv)
//       Each should print a label indicating which overload was called.

// ── 2. Default arguments ──────────────────────────────────────────────────────
// TODO: Define `greet(std::string_view name, std::string_view prefix = "Hello")`
//       that prints "<prefix>, <name>!".

// ── 3. constexpr functions ────────────────────────────────────────────────────
// TODO: Implement `constexpr int factorial(int n)` recursively.
// TODO: Implement `constexpr double deg_to_rad(double deg)`.
// TODO: After implementing, add a static_assert to verify factorial(5) == 120
//       at compile time.

// ── 4. [[nodiscard]] ─────────────────────────────────────────────────────────
// TODO: Declare a function `[[nodiscard]] int compute_checksum(int data)`
//       that returns data * 31 + 7. Then in main, try calling it without storing
//       the result — observe the compiler warning.

// ── 5. Namespaces ────────────────────────────────────────────────────────────
// TODO: Create a namespace `math` containing:
//         constexpr double pi = 3.14159265358979323846;
//         double circle_area(double r)   // returns pi * r * r
//
//       Inside `math`, create a nested namespace `geometry` containing:
//         double hypotenuse(double a, double b)  // sqrt(a*a + b*b)

// TODO: Create an `api` namespace with an inline namespace `v2` and a regular
//       `v1` namespace, each containing `void run()` that prints its version.
//       Call `api::run()` (should call v2) and `api::v1::run()` explicitly.

// ── 6. Argument-Dependent Lookup (ADL) ───────────────────────────────────────
// TODO: In a namespace `sensors`, define a struct `Temperature { double celsius; }`
//       and a free function `void log(const Temperature& t)`.
//       In main, call `log(temp)` without qualification — ADL should find it.

// ── 7. std::string_view ──────────────────────────────────────────────────────
// TODO: Write `std::size_t count_vowels(std::string_view sv)` that counts
//       lowercase vowels (a, e, i, o, u) in the view without copying the string.

// ── 8. Inline variable (C++17) ───────────────────────────────────────────────
// TODO: Declare `inline constexpr double gravity_mps2 = 9.80665;` at namespace
//       scope and print it in main.

int main() {
    std::cout << "=== 02: Functions & Scope ===\n\n";

    // TODO: Call each overload of print with an int, double, and string literal.

    // TODO: Call greet with one argument, then with two.

    // TODO: Print factorial(5) and deg_to_rad(90.0).

    // TODO: Demonstrate [[nodiscard]] — store the result and use it.

    // TODO: Call math::circle_area and math::geometry::hypotenuse.

    // TODO: Demonstrate inline namespace: api::run() and api::v1::run().

    // TODO: Demonstrate ADL with sensors::Temperature.

    // TODO: Call count_vowels with a std::string and a string literal directly.

    // TODO: Print gravity_mps2.

    return 0;
}
