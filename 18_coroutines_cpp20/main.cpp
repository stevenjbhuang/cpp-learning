/*
 * ============================================================
 * Module 18 — Coroutines (C++20)
 * ============================================================
 *
 * Coroutines are functions that can be suspended and resumed.
 * They enable cooperative multitasking, generators, and
 * asynchronous code that reads like synchronous code —
 * without allocating OS threads.
 *
 * Key concepts:
 *
 * 1. Coroutine keywords
 *    - co_yield expr  : suspend and produce a value
 *    - co_return expr : finish the coroutine (optionally with a value)
 *    - co_await expr  : suspend until an awaitable is ready
 *    - A function containing any of these is a coroutine
 *
 * 2. The coroutine machinery
 *    - promise_type: a nested type in the return object that controls behaviour
 *      at suspension/resumption points
 *    - coroutine_handle<promise_type>: a lightweight handle to resume/destroy
 *    - Coroutine frame: heap-allocated (usually) state preserved across suspensions
 *    - Return object: what the caller receives; wraps the coroutine_handle
 *
 * 3. Generator pattern (co_yield)
 *    - Produce a sequence of values lazily on demand
 *    - Caller pulls next value with operator++ on an iterator
 *    - std::generator<T> from <generator> (C++23) — standard generator type
 *    - Implementing a minimal Generator<T> yourself teaches the machinery
 *
 * 4. Task / async pattern (co_await)
 *    - Suspend waiting for an async result
 *    - An "awaitable" implements await_ready(), await_suspend(), await_resume()
 *    - Trivial awaitable: std::suspend_always, std::suspend_never
 *    - Full coroutine scheduler (Module 25) builds on these primitives
 *
 * 5. Symmetric transfer
 *    - await_suspend can return a coroutine_handle to resume immediately
 *    - Avoids stack growth when chaining coroutines
 *
 * 6. Coroutine lifetime & destruction
 *    - The coroutine_handle must be destroyed exactly once
 *    - Destroying a suspended coroutine runs destructors of local variables
 *    - RAII handles this automatically if the return object owns the handle
 *
 * Build & run:
 *   make run MODULE=18_coroutines_cpp20
 * ============================================================
 */

#include <coroutine>
#include <cstdint>
#include <iostream>
#include <optional>
#include <string>

// ── 1. Minimal Generator<T> ───────────────────────────────────────────────────
// TODO: Implement Generator<T> — a coroutine return type for co_yield sequences.
//
//   template <typename T>
//   struct Generator {
//     struct promise_type {
//       T current_value;
//       Generator get_return_object()   { return Generator{...}; }
//       std::suspend_always initial_suspend() { return {}; }
//       std::suspend_always final_suspend() noexcept { return {}; }
//       std::suspend_always yield_value(T v) { current_value = v; return {}; }
//       void return_void() {}
//       void unhandled_exception() { std::terminate(); }
//     };
//
//     // Iterator that drives the coroutine
//     struct iterator { ... operator++, operator*, operator!= ... };
//     iterator begin() { handle_.resume(); return {handle_}; }
//     std::default_sentinel_t end() { return {}; }
//
//     // RAII handle ownership
//     explicit Generator(std::coroutine_handle<promise_type> h) : handle_(h) {}
//     ~Generator() { if (handle_) handle_.destroy(); }
//     Generator(const Generator&) = delete;
//     Generator(Generator&& o) noexcept : handle_(std::exchange(o.handle_, {})) {}
//
//   private:
//     std::coroutine_handle<promise_type> handle_;
//   };

// ── 2. Generator coroutines ───────────────────────────────────────────────────
// TODO: Write `Generator<int> range(int from, int to)` using co_yield.
// TODO: Write `Generator<uint64_t> fibonacci()` — infinite sequence.
// TODO: Write `Generator<std::string> tokenise(std::string text)` that
//       co_yields each whitespace-separated word.

// ── 3. Minimal Task<T> — a resumable async computation ───────────────────────
// TODO: Implement Task<T> — a one-shot coroutine that produces a value
//       via co_return.
//
//   template <typename T>
//   struct Task {
//     struct promise_type {
//       std::optional<T> result;
//       Task get_return_object()         { return Task{...}; }
//       std::suspend_never initial_suspend() { return {}; }  // eager start
//       std::suspend_always final_suspend() noexcept { return {}; }
//       void return_value(T v) { result = std::move(v); }
//       void unhandled_exception() { std::terminate(); }
//     };
//
//     T get() { return *handle_.promise().result; }
//     explicit Task(std::coroutine_handle<promise_type> h) : handle_(h) {}
//     ~Task() { if (handle_) handle_.destroy(); }
//     // ... move-only
//   };

// TODO: Write `Task<int> compute_answer()` that co_returns 42.
// TODO: Write `Task<std::string> greet(std::string name)` that
//       co_returns "Hello, " + name.

// ── 4. Custom awaitable ───────────────────────────────────────────────────────
// TODO: Implement `struct ReadyAwaitable` that wraps a value and is always ready:
//   bool await_ready() const { return true; }
//   void await_suspend(std::coroutine_handle<>) const {}
//   T await_resume() const { return value; }
//
// TODO: Write a coroutine that co_awaits a ReadyAwaitable<int> and adds to it.

int main() {
    std::cout << "=== 18: Coroutines (C++20) ===\n\n";

    std::cout << "-- Generator: range(1,6) --\n";
    // TODO: for (auto v : range(1, 6)) print v.

    std::cout << "\n-- Generator: fibonacci first 10 --\n";
    // TODO: Take first 10 values from fibonacci() using a counter or views::take.

    std::cout << "\n-- Generator: tokenise --\n";
    // TODO: tokenise("hello world foo bar") and print each token.

    std::cout << "\n-- Task --\n";
    // TODO: auto t = compute_answer(); print t.get().
    // TODO: auto g = greet("Coroutine"); print g.get().

    std::cout << "\n-- Custom awaitable --\n";
    // TODO: Demonstrate co_await ReadyAwaitable in a Task coroutine.

    return 0;
}
