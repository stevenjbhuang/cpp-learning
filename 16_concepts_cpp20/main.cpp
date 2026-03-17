/*
 * ============================================================
 * Module 16 — Concepts (C++20)
 * ============================================================
 *
 * Concepts are named, compile-time predicates on template
 * parameters. They replace SFINAE and tag dispatch with readable
 * constraints, and produce far better error messages when a type
 * does not satisfy the requirements.
 *
 * Key concepts:
 *
 * 1. Defining a concept
 *    - `template <typename T> concept Name = <boolean expression>;`
 *    - The boolean expression can use type traits, requires expressions,
 *      or compose other concepts with &&, ||, !
 *
 * 2. requires expressions
 *    - Simple: requires (T t) { t.foo(); }  — checks t.foo() is well-formed
 *    - Type:   requires { typename T::value_type; }
 *    - Compound (with return type): requires (T t) { { t.size() } -> std::convertible_to<std::size_t>; }
 *    - Nested requires: requires (T t) { requires sizeof(T) == 4; }
 *
 * 3. Constraining templates
 *    - requires clause after template params:
 *        template <typename T> requires Numeric<T> T add(T a, T b);
 *    - Shorthand (terse syntax):
 *        Numeric auto add(Numeric auto a, Numeric auto b);
 *    - Concept as template parameter:
 *        template <Numeric T> T add(T a, T b);
 *
 * 4. Standard library concepts (<concepts>)
 *    - std::integral, std::floating_point, std::arithmetic
 *    - std::same_as<T,U>, std::convertible_to<From,To>
 *    - std::derived_from<Derived,Base>
 *    - std::invocable<F,Args...>, std::predicate<F,Args...>
 *    - std::ranges::range, std::ranges::sized_range, std::ranges::random_access_range
 *
 * 5. Concept subsumption
 *    - When two constrained overloads both match, the more constrained one wins
 *    - Requires concepts to be expressed in terms of each other (not repeated predicates)
 *
 * 6. Abbreviated function templates
 *    - `auto` parameters implicitly create a function template
 *    - `Concept auto` constrains that implicit template parameter
 *
 * Build & run:
 *   make run MODULE=16_concepts_cpp20
 * ============================================================
 */

#include <concepts>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

// ── 1. Define custom concepts ─────────────────────────────────────────────────
// TODO: Define concept `Numeric` that is satisfied by integral or floating-point types.
//       Use: std::integral<T> || std::floating_point<T>

// TODO: Define concept `Printable` that requires a type to be usable with operator<<:
//   requires (std::ostream& os, const T& t) { os << t; }

// TODO: Define concept `Container` that requires:
//   - T::value_type exists
//   - t.begin() and t.end() return iterators
//   - t.size() returns a type convertible to std::size_t

// ── 2. Constrained function templates ────────────────────────────────────────
// TODO: Implement `Numeric auto square(Numeric auto x)` that returns x*x.
//       Call it with int and double; confirm it refuses std::string (comment).

// TODO: Implement `template <Numeric T> T clamp(T val, T lo, T hi)`.

// TODO: Implement `void print_container(const Container auto& c)` that
//       prints each element using range-for.

// ── 3. requires clause — more expressive constraints ──────────────────────────
// TODO: Define concept `Serializable`:
//   requires (T t) {
//       { t.serialize() } -> std::convertible_to<std::string>;
//   }
//
// TODO: Implement a struct `SensorReading { float value; std::string serialize() const; }`
// TODO: Write `void send(const Serializable auto& item)` that prints item.serialize().

// ── 4. Concept subsumption ────────────────────────────────────────────────────
// TODO: Define concept `SignedInteger` that refines `Numeric` by also requiring std::signed_integral.
//
// TODO: Write two overloads of `describe(auto val)`:
//   - Constrained by Numeric:       prints "numeric"
//   - Constrained by SignedInteger: prints "signed integer"  (more constrained — wins)
//
// NOTE: For subsumption to work, SignedInteger must be defined as:
//   concept SignedInteger = Numeric<T> && std::signed_integral<T>;

// ── 5. Standard concepts usage ────────────────────────────────────────────────
// TODO: Write `template <std::invocable<int> F> int apply_to_5(F&& f)`.
//       Call it with a lambda, a free function, and a functor.

// TODO: Write a function constrained by std::ranges::random_access_range
//       that returns the middle element of a range.

int main() {
    std::cout << "=== 16: Concepts (C++20) ===\n\n";

    std::cout << "-- Custom concepts --\n";
    // TODO: Call square(3), square(2.5).
    // TODO: Call clamp(15, 0, 10). Print result.

    std::cout << "\n-- Container concept --\n";
    // TODO: Call print_container with vector<int> and string.

    std::cout << "\n-- Serializable --\n";
    // TODO: Call send(SensorReading{9.81f}).

    std::cout << "\n-- Subsumption --\n";
    // TODO: Call describe(42), describe(3.14), describe(-7).

    std::cout << "\n-- Standard concepts --\n";
    // TODO: Call apply_to_5([](int x){ return x*x; }).
    // TODO: Call middle_element on a vector<int>{1,2,3,4,5}.

    return 0;
}
