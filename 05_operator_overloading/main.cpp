/*
 * ============================================================
 * Module 05 — Operator Overloading (C++17/20)
 * ============================================================
 *
 * Operator overloading lets user-defined types behave like
 * built-in types in expressions. Good overloads follow the
 * Principle of Least Surprise: they should behave the way
 * users expect built-in operators to behave.
 *
 * Key concepts:
 *
 * 1. Arithmetic operators (+, -, *, +=)
 *    - Prefer non-member (free function) for symmetry: a+b == b+a
 *    - Implement op= first, then derive op from it:
 *        T operator+(T lhs, const T& rhs) { return lhs += rhs; }
 *    - Unary minus: `T operator-() const`
 *
 * 2. Comparison operators
 *    - Pre-C++20: define == and <, derive the rest with <utility> rel_ops
 *    - C++20: define `operator<=>` (spaceship) once and get all six for free
 *    - `= default` spaceship compares members lexicographically
 *
 * 3. Stream I/O operators
 *    - `operator<<` and `operator>>` must be free functions
 *    - Declare as `friend` inside the class if private member access is needed
 *    - Return the stream by reference to allow chaining: cout << a << b;
 *
 * 4. Subscript operator []
 *    - Provide both const and non-const overloads
 *    - The const overload should return `const T&`
 *    - Used for array-like or container types
 *
 * 5. Call operator () — functors
 *    - Makes an object callable like a function
 *    - Carries state between calls (unlike plain function pointers)
 *    - Foundation of lambdas: a lambda is syntactic sugar for a functor
 *
 * 6. Conversion operators
 *    - `operator T() const` — implicit conversion (usually dangerous)
 *    - `explicit operator T() const` — must use static_cast<T>()
 *    - Converting constructors: `Foo(Bar b)` — implicit; add `explicit` to opt out
 *
 * Build & run:
 *   make run MODULE=05_operator_overloading
 * ============================================================
 */

#include <compare>
#include <iostream>
#include <string>
#include <vector>

// ── 1. Vec2 — arithmetic + comparison ────────────────────────────────────────
// TODO: Implement struct Vec2 { double x{}, y{}; } with:
//   Member operators:
//     Vec2 operator+(const Vec2& rhs) const
//     Vec2 operator-(const Vec2& rhs) const
//     Vec2 operator*(double s) const
//     Vec2& operator+=(const Vec2& rhs)
//     Vec2 operator-() const            — unary minus
//   Spaceship (C++20, defaulted — generates ==, !=, <, <=, >, >=):
//     auto operator<=>(const Vec2&) const = default;
//   Friend stream output:
//     friend std::ostream& operator<<(std::ostream&, const Vec2&)
//       — format: "(x, y)"
//
// TODO: Also add a free (non-member) function for scalar-on-the-left:
//   Vec2 operator*(double s, const Vec2& v)

// ── 2. RingBuffer — subscript operator ───────────────────────────────────────
// TODO: Implement template class RingBuffer<T>:
//   - Constructor: explicit RingBuffer(std::size_t capacity)
//   - void push(const T& val)  — overwrites oldest entry when full
//   - const T& operator[](std::size_t idx) const
//       logical index 0 = oldest element, size-1 = newest
//   - std::size_t size() const
//   Private: std::vector<T> buf_, size_t cap_, write_pos_{0}, size_{0}
//
// HINT: oldest element lives at physical index (write_pos_ - size_ + idx + cap_) % cap_

// ── 3. PIDController — call operator (functor) ───────────────────────────────
// TODO: Implement struct PIDController { double kp, ki, kd; ... }
//   with an `operator()(double error, double dt)` that:
//     - Accumulates integral += error * dt
//     - Computes derivative = (error - prev_error) / dt
//     - Returns kp*error + ki*integral + kd*derivative
//   Private state: double integral{}, prev_error{}

// ── 4. Conversion operators ───────────────────────────────────────────────────
// TODO: Implement struct Celsius { double value; }
//   with `explicit operator double() const` returning value.
//
// TODO: Implement struct Fahrenheit { double value; }
//   with a converting constructor from Celsius: value = c.value * 9/5 + 32
//   and a friend operator<< that prints "<value>°F".

int main() {
    std::cout << "=== 05: Operator Overloading ===\n\n";

    // Vec2
    std::cout << "-- Vec2 --\n";
    // TODO: Create Vec2 a{1,2} and b{3,4}.
    // TODO: Print a+b, a-b, 2.0*a, a*3.0.
    // TODO: Test a==a, a<b; print results.
    // TODO: Use a += b and print the result.

    // RingBuffer
    std::cout << "\n-- RingBuffer --\n";
    // TODO: Create RingBuffer<int> ring(4).
    // TODO: Push 10, 20, 30, 40, 50 (50 overwrites 10).
    // TODO: Print size, oldest element [0], newest element [size-1].

    // PIDController
    std::cout << "\n-- PIDController (functor) --\n";
    // TODO: Create PIDController pid{1.0, 0.1, 0.05}.
    // TODO: Call pid(5.0, 0.01) and print the output.
    // TODO: Call it again with a different error to show stateful integral.

    // Conversion
    std::cout << "\n-- Conversion operators --\n";
    // TODO: Celsius temp{100.0}; Fahrenheit f = temp; print f.
    // TODO: Use static_cast<double>(temp) to get the raw value.

    return 0;
}
