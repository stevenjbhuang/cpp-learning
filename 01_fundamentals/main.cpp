/*
 * ============================================================
 * Module 01 — Fundamentals (C++17)
 * ============================================================
 *
 * This module introduces the building blocks of modern C++.
 *
 * Key concepts:
 *
 * 1. Primitive types & type aliases
 *    - Integral types: int, long, long long, unsigned variants
 *    - Floating-point types: float, double
 *    - char, bool, their sizes and ranges
 *    - Fixed-width types from <cstdint>: int32_t, uint64_t, etc.
 *    - Digit separators for readability: 1'000'000
 *    - `auto` for type deduction — when to use it, when not to
 *
 * 2. Structured bindings (C++17)
 *    - Decomposing std::pair, std::tuple, arrays, and structs
 *    - Syntax: auto [a, b] = expr;
 *    - Use in range-based for loops over maps
 *
 * 3. Range-based for loop
 *    - `for (const auto& v : container)` vs `for (auto v : container)`
 *    - Modifying elements: `for (auto& v : container)`
 *    - Works with any type that provides begin()/end()
 *
 * 4. if / switch with initializer statements (C++17)
 *    - Scope-limiting variables to the branch: if (int x = f(); x > 0)
 *    - Same for switch: switch (int c = get(); c)
 *
 * 5. std::string basics
 *    - Construction, concatenation, substr, find, size
 *    - String literals: "hello"s (std::string), "hello"sv (string_view)
 *    - Avoid implicit conversions from const char* in function signatures
 *
 * Build & run:
 *   make run MODULE=01_fundamentals
 * ============================================================
 */

#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <tuple>

// ── 1. Primitive types & auto ─────────────────────────────────────────────────
void demo_types() {
    // TODO: Declare variables of the following types and print their values:
    //   - int, long long (use digit separator: 9'000'000'000LL)
    //   - double, float (note the 'f' suffix)
    //   - bool, char
    //   - unsigned int using a hex literal (e.g. 0xDEAD'BEEFu)
    //   - Use `auto` for at least three variables and note the deduced type
    //     in a comment next to each declaration

    // TODO: Print the sizeof() each type. Notice which are 4 bytes vs 8 bytes.

    // TODO: Declare a uint32_t and int64_t from <cstdint> and print them.
    //       Why are fixed-width types preferred in networking/serialization code?
}

// ── 2. Structured bindings (C++17) ───────────────────────────────────────────
void demo_structured_bindings() {
    // TODO: Create a std::pair<int, std::string> and decompose it with auto [].

    // TODO: Declare an int array of size 3 and bind its elements with auto [].

    // TODO: Create a std::tuple<float, int, bool> and decompose it.

    // TODO: Create a std::map<std::string, int> with a few entries and iterate
    //       over it using `for (const auto& [key, value] : map)`. Print each pair.
}

// ── 3. Range-based for loop ───────────────────────────────────────────────────
void demo_range_for() {
    std::array<int, 5> arr = {5, 10, 15, 20, 25};

    // TODO: Print all elements using a range-for with `const auto&`.

    // TODO: Double every element in-place using a range-for with `auto&`.

    // TODO: Print the doubled values to verify.
}

// ── 4. if / switch with initializer (C++17) ──────────────────────────────────
void demo_init_statements() {
    // TODO: Write an if statement with an initializer that calls a lambda
    //       returning an int. Use the variable only inside the if/else branch.
    //       Verify the variable is not accessible outside the block (a comment
    //       showing the compile error is enough).

    // TODO: Write a switch statement with an initializer.
    //       The initializer should call a lambda `auto get_code = []{ return 2; }`.
    //       Handle cases 1, 2, and a default.
}

// ── 5. std::string basics ────────────────────────────────────────────────────
void demo_strings() {
    // TODO: Construct a std::string, print its size() and capacity().

    // TODO: Use substr(), find(), and rfind(). Print the results.

    // TODO: Append with += and with append(). Print after each.

    // TODO: Use the "s" string literal suffix (std::string_view in C++17):
    //         using namespace std::string_literals;
    //         auto s = "hello"s;   // type is std::string, not const char*
    //       Explain in a comment why this matters.
}

int main() {
    std::cout << "=== 01: Fundamentals ===\n\n";

    std::cout << "-- Types & auto --\n";
    demo_types();

    std::cout << "\n-- Structured bindings --\n";
    demo_structured_bindings();

    std::cout << "\n-- Range-based for --\n";
    demo_range_for();

    std::cout << "\n-- if/switch initializers --\n";
    demo_init_statements();

    std::cout << "\n-- std::string --\n";
    demo_strings();

    return 0;
}
