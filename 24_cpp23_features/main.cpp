/*
 * ============================================================
 * Module 24 — C++23 Features
 * ============================================================
 *
 * C++23 is a smaller refinement release compared to C++20,
 * but introduces several ergonomic improvements and long-awaited
 * library additions that directly affect everyday code.
 *
 * Key concepts:
 *
 * 1. std::print / std::println (<print>)
 *    - Type-safe, format-string printing built on std::format
 *    - std::print(stdout, "value = {}\n", x);
 *    - std::println("hello {}", name);  // adds newline automatically
 *    - Much faster than cout in many implementations (direct buffered output)
 *
 * 2. std::expected<T, E> (<expected>)
 *    - Covered in Module 09; here focus on monadic operations:
 *    - .and_then(fn)  — apply fn to value if present; returns expected
 *    - .or_else(fn)   — apply fn to error if present
 *    - .transform(fn) — map value; equivalent to Rust's .map()
 *    - Enables pipeline-style error propagation without exceptions
 *
 * 3. std::flat_map / std::flat_set (<flat_map>)
 *    - Sorted key-value container backed by two flat arrays
 *    - Better cache performance than std::map (no tree node pointers)
 *    - O(log n) find, O(n) insert/erase (must shift arrays)
 *    - Best for read-heavy workloads with infrequent modifications
 *
 * 4. std::mdspan (<mdspan>)
 *    - Multi-dimensional non-owning view over contiguous data
 *    - Replaces raw pointer+stride arithmetic for matrices/tensors
 *    - Syntax: std::mdspan<float, std::extents<int,3,4>> m(data);
 *    - Access: m[i, j] (C++23) or m(i, j)
 *    - Layout policies: row_major (default), column_major, strided
 *
 * 5. Deducing this (explicit object parameter)
 *    - template <typename Self> RetType fn(this Self&& self, ...)
 *    - Deduces const/ref qualifiers from the call site
 *    - Replaces CRTP in many cases with simpler syntax
 *    - Enables recursive lambdas: [](this auto& self, int n){ ... }
 *
 * 6. std::ranges::to<Container>
 *    - Materialise a range/view into a container:
 *        auto v = iota(1,11) | views::transform(sq) | ranges::to<vector>();
 *    - Works with any range and any constructible container
 *
 * 7. Monadic operations on std::optional
 *    - .and_then(fn)  — if has_value, apply fn (must return optional)
 *    - .or_else(fn)   — if no value, apply fn (must return optional)
 *    - .transform(fn) — if has_value, apply fn and wrap result in optional
 *
 * Build & run:
 *   make run MODULE=24_cpp23_features
 * ============================================================
 */

#include <expected>
#include <flat_map>
#include <iostream>
#include <mdspan>
#include <optional>
#include <print>
#include <ranges>
#include <string>
#include <vector>

// ── 1. std::print / std::println ─────────────────────────────────────────────
void demo_print() {
    // TODO: Use std::println to print a greeting with a name and an integer.
    // TODO: Use std::print (no newline) followed by std::println.
    // TODO: Print a float with 2 decimal places: std::println("{:.2f}", 3.14159);
    // TODO: Print a table of squares using std::println("{:>4}: {:>6}", i, i*i)
    //       for i in 1..10. Observe the right-alignment formatting.
}

// ── 2. std::expected monadic operations ──────────────────────────────────────
// TODO: Write `std::expected<double, std::string> safe_sqrt(double x)`:
//   - Return unexpected("negative input") if x < 0
//   - Return std::sqrt(x) otherwise.
//
// TODO: Write `std::expected<double, std::string> safe_reciprocal(double x)`:
//   - Return unexpected("division by zero") if x == 0
//   - Return 1.0 / x otherwise.

void demo_expected_monadic() {
    // TODO: Chain safe_sqrt and safe_reciprocal using .and_then():
    //   auto result = safe_sqrt(4.0).and_then(safe_reciprocal);
    //   Print result.value() or result.error().
    //
    // TODO: Try with -1.0 to propagate an error through the chain.
    //
    // TODO: Use .transform([](double v){ return v * 100.0; }) on a success result.
    //
    // TODO: Use .or_else to substitute a default value on error.
}

// ── 3. std::flat_map ─────────────────────────────────────────────────────────
void demo_flat_map() {
    // TODO: Create std::flat_map<std::string, int> with sensor name → priority.
    // TODO: Insert entries, find, and erase. Print the map.
    // TODO: Compare with std::map for the same operations — comment on trade-offs.
    // TODO: Print the underlying keys() and values() vectors to show flat storage.
}

// ── 4. std::mdspan ────────────────────────────────────────────────────────────
void demo_mdspan() {
    // TODO: Create a raw float array of 3*4 elements.
    //       Wrap it in a 3×4 mdspan:
    //         std::mdspan<float, std::extents<int, 3, 4>> m(data);
    // TODO: Fill it with i*4+j values. Print as a matrix.
    // TODO: Demonstrate element access: m[i, j] and m.extent(0), m.extent(1).
    // TODO: Pass the mdspan to a function that computes the row sums.
}

// ── 5. Deducing this ─────────────────────────────────────────────────────────
// TODO: Implement struct Builder using deducing this for method chaining:
//
//   struct Builder {
//     std::string name;
//     int value{0};
//
//     template <typename Self>
//     Self& set_name(this Self& self, std::string n) {
//         self.name = std::move(n); return self;
//     }
//     template <typename Self>
//     Self& set_value(this Self& self, int v) {
//         self.value = v; return self;
//     }
//     std::string build() const;
//   };
//
// TODO: Chain: Builder{}.set_name("sensor").set_value(42).build()
//
// TODO: Also write a recursive lambda using deducing this:
//   auto fib = [](this auto& self, int n) -> int {
//       return n <= 1 ? n : self(n-1) + self(n-2);
//   };

// ── 6. ranges::to ────────────────────────────────────────────────────────────
void demo_ranges_to() {
    // TODO: Build a pipeline with iota + filter + transform.
    //       Materialise into std::vector<int> using ranges::to<std::vector>().
    // TODO: Print size and contents.
    // TODO: Materialise into std::flat_map<int,int> using ranges::to.
}

// ── 7. std::optional monadic operations ──────────────────────────────────────
void demo_optional_monadic() {
    // TODO: Write a chain of operations on optional<string>:
    //   opt.transform(to_uppercase)
    //      .and_then(check_length)
    //      .or_else([]{ return std::optional<string>{"default"}; })
    //
    // TODO: Test with a value present and with std::nullopt.
}

int main() {
    std::cout << "=== 24: C++23 Features ===\n\n";

    std::cout << "-- std::print --\n";               demo_print();
    std::cout << "\n-- expected monadic --\n";        demo_expected_monadic();
    std::cout << "\n-- flat_map --\n";                demo_flat_map();
    std::cout << "\n-- mdspan --\n";                  demo_mdspan();
    std::cout << "\n-- deducing this --\n";
    // TODO: Call Builder chain and recursive fib lambda.
    std::cout << "\n-- ranges::to --\n";              demo_ranges_to();
    std::cout << "\n-- optional monadic --\n";        demo_optional_monadic();

    return 0;
}
