/*
 * ============================================================
 * Module 12 — Lambdas & Functional Programming (C++17)
 * ============================================================
 *
 * Lambdas are anonymous function objects (closures). They capture
 * surrounding variables and can be stored, passed, and returned
 * like any value. Together with std::function and higher-order
 * algorithms, they enable a functional style in C++.
 *
 * Key concepts:
 *
 * 1. Lambda syntax
 *    - [capture](params) -> return_type { body }
 *    - Return type is optional (deduced from body in most cases)
 *    - Immediately invoked: [](int x){ return x*2; }(5)
 *
 * 2. Capture modes
 *    - [=]   capture all by value (copy at definition time)
 *    - [&]   capture all by reference
 *    - [x]   capture x by value
 *    - [&x]  capture x by reference
 *    - [=, &x] default by value, x by reference
 *    - [this] capture the enclosing object pointer
 *    - C++14: [x = expr] init-capture (move into the closure)
 *
 * 3. Mutable lambdas
 *    - By default, value-captured variables are const in the body
 *    - Add `mutable` to allow modification of the captured copy
 *
 * 4. Generic lambdas (C++14)
 *    - Use `auto` parameters: [](auto x, auto y){ return x + y; }
 *    - The compiler generates a templated operator()
 *
 * 5. std::function<R(Args...)>
 *    - Type-erased callable — stores any callable with matching signature
 *    - Overhead: heap allocation (usually) + virtual dispatch
 *    - Prefer templates / auto for performance-critical code
 *    - Use std::function for APIs that must store heterogeneous callables
 *
 * 6. Higher-order functions
 *    - Functions that take or return functions
 *    - compose(f, g)(x) == f(g(x))
 *    - curry, partial application
 *    - Pipelines: chaining transforms
 *
 * 7. std::bind (legacy) vs lambdas
 *    - std::bind is verbose and hard to read; lambdas are preferred in C++14+
 *    - Know std::bind for reading legacy code
 *    - std::placeholders::_1, _2 for argument placeholders
 *
 * Build & run:
 *   make run MODULE=12_lambdas_functionals
 * ============================================================
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// ── 1. Lambda basics & captures ───────────────────────────────────────────────
void demo_captures() {
    int x = 10, y = 20;

    // TODO: Create a lambda that captures x by value. Modify x after creation.
    //       Call the lambda and show the captured value did NOT change.

    // TODO: Create a lambda that captures y by reference.
    //       Modify y after creation, call the lambda — value SHOULD reflect the change.

    // TODO: Use init-capture to move a string into the closure:
    //         auto fn = [s = std::string("hello")](){ ... };

    // TODO: Write a mutable lambda with a value-captured counter that increments
    //       each time it's called. Call it 3 times and print the counter.
}

// ── 2. Generic lambda ────────────────────────────────────────────────────────
void demo_generic_lambda() {
    // TODO: Write a generic lambda `add` that takes two auto params and returns their sum.
    //       Call it with (int,int), (double,double), and (std::string, std::string).

    // TODO: Write a generic lambda that prints any container using range-for.
    //       Call it with a vector<int> and a vector<string>.
}

// ── 3. std::function ─────────────────────────────────────────────────────────
// TODO: Define `using Transform = std::function<int(int)>;`
//
// TODO: Write `int apply(int val, const Transform& fn)` that applies fn to val.
//
// TODO: Create a std::vector<Transform> pipeline = { square, negate, add5 }
//       and reduce it by chaining: fold each transform over an initial value.

void demo_std_function() {
    // TODO: Store a free function, a lambda, and a functor in Transform variables.
    //       Call apply() with each.
    // TODO: Build a pipeline and apply it to the value 3. Print intermediate results.
}

// ── 4. Higher-order functions ────────────────────────────────────────────────
// TODO: Implement `template <typename F, typename G>`
//       auto compose(F f, G g) — returns a lambda [=](auto x){ return f(g(x)); }
//
// TODO: Implement `template <typename F>`
//       auto memoize(F f) — wraps f in a std::unordered_map<int,int> cache.
//       (Simplify: assume int->int for the cache key/value type.)

void demo_higher_order() {
    // TODO: Compose double_it and add_one; apply to 5.
    // TODO: Memoize a slow Fibonacci and call it multiple times. Time the difference.
    //       (Use a simple loop counter instead of actual timing if preferred.)
}

// ── 5. std::bind (legacy) vs lambda ──────────────────────────────────────────
void demo_bind() {
    auto multiply = [](int a, int b) { return a * b; };

    // TODO: Use std::bind to create a "double" function (bind second arg to 2).
    //       Equivalent lambda: [multiply](int x){ return multiply(x, 2); }
    // TODO: Print both results and confirm they are identical.
    // TODO: In a comment, explain why lambdas are generally preferred over bind.
}

int main() {
    std::cout << "=== 12: Lambdas & Functionals ===\n\n";

    std::cout << "-- Captures --\n";         demo_captures();
    std::cout << "\n-- Generic lambda --\n";  demo_generic_lambda();
    std::cout << "\n-- std::function --\n";   demo_std_function();
    std::cout << "\n-- Higher-order --\n";    demo_higher_order();
    std::cout << "\n-- std::bind --\n";       demo_bind();

    return 0;
}
