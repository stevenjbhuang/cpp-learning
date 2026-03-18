/*
 * ============================================================
 * Module 25 — Advanced Coroutines (C++20)
 * ============================================================
 *
 * Building on Module 18's introduction, this module implements
 * a cooperative coroutine scheduler capable of running many
 * concurrent tasks on a single thread — the foundation of
 * async I/O frameworks like Asio and liburing wrappers.
 *
 * Key concepts:
 *
 * 1. Symmetric transfer
 *    - await_suspend returns coroutine_handle<> instead of void
 *    - The runtime resumes that handle immediately (tail call)
 *    - Prevents stack growth when thousands of coroutines chain together
 *    - Critical for scalable coroutine schedulers
 *
 * 2. Coroutine scheduler
 *    - Maintains a queue of ready coroutine_handles
 *    - schedule(handle): enqueue; run_until_empty(): drain the queue
 *    - Tasks yield by co_awaiting a "schedule" awaitable that re-enqueues
 *      the coroutine on the scheduler's queue
 *
 * 3. Awaitable design
 *    - await_ready(): return true to skip suspension (fast path)
 *    - await_suspend(handle): receive the suspended coroutine's handle;
 *      store it for later resumption; return void/bool/handle
 *    - await_resume(): called when the coroutine is resumed; returns the value
 *
 * 4. Chaining coroutines (co_await Task)
 *    - A Task<T> is awaitable if its promise stores the continuation handle
 *    - When the inner task finishes, it resumes the outer coroutine
 *    - This is the "structured concurrency" pattern
 *
 * 5. Cancellation
 *    - Inject a std::stop_token into the coroutine frame
 *    - Check stop_token.stop_requested() at co_await points
 *    - On cancellation, co_return early with an error / sentinel
 *
 * 6. Exception handling in coroutines
 *    - promise_type::unhandled_exception() is called on uncaught throw
 *    - Store via std::current_exception(); rethrow at .get() / await_resume()
 *    - Task<T> with exception propagation: store exception_ptr in promise
 *
 * Build & run:
 *   make run MODULE=25_advanced_coroutines
 * ============================================================
 */

#include <coroutine>
#include <exception>
#include <functional>
#include <iostream>
#include <optional>
#include <queue>
#include <string>
#include <utility>

// ── 1. Scheduler ─────────────────────────────────────────────────────────────
// TODO: Implement class Scheduler:
//
//   std::queue<std::coroutine_handle<>> ready_;
//
//   void schedule(std::coroutine_handle<> h) { ready_.push(h); }
//
//   void run() {
//     while (!ready_.empty()) {
//       auto h = ready_.front(); ready_.pop();
//       if (!h.done()) h.resume();
//     }
//   }
//
// TODO: Make a global (or thread-local) scheduler instance accessible to awaitables.

// ── 2. Yield awaitable — voluntarily give up the CPU ─────────────────────────
// TODO: Implement struct YieldAwaitable:
//   bool await_ready() { return false; }      // always suspend
//   void await_suspend(coroutine_handle<> h) {
//       scheduler.schedule(h);               // re-enqueue self
//   }
//   void await_resume() {}
//
// TODO: Write a helper function:
//   YieldAwaitable yield_to_scheduler() { return {}; }

// ── 3. Task<T> with exception propagation ────────────────────────────────────
// TODO: Extend the Task<T> from Module 18 with:
//   - promise_type stores std::exception_ptr alongside the result
//   - unhandled_exception() captures std::current_exception()
//   - get() rethrows if exception_ptr is set
//   - Task<T> is awaitable (await_suspend stores the continuation in the promise;
//     final_suspend resumes it via symmetric transfer)

// ── 4. Coroutine tasks using the scheduler ────────────────────────────────────
// TODO: Write `Task<void> task_a(std::string name, int steps)`:
//   - Loop `steps` times: print "[name] step i", then co_await yield_to_scheduler()
//   - Print "[name] done"
//
// TODO: Write `Task<int> compute(int n)`:
//   - Simulates a multi-step computation: yields after each step
//   - co_returns the result after `n` steps

// ── 5. Chained tasks ─────────────────────────────────────────────────────────
// TODO: Write `Task<void> outer_task()`:
//   - Spawns compute(5) and co_awaits it: int result = co_await compute(5);
//   - Prints the result.
//   - Then yields once more.

// ── 6. Exception in coroutine ────────────────────────────────────────────────
// TODO: Write `Task<int> failing_task()`:
//   - Yields once, then throws std::runtime_error("coroutine error")
//
// TODO: In a wrapper task, co_await failing_task() inside try/catch.
//       Print the caught exception message.

int main() {
    std::cout << "=== 25: Advanced Coroutines ===\n\n";

    // TODO: Schedule task_a("A", 3) and task_a("B", 3).
    //       Run the scheduler and observe interleaved output.
    std::cout << "-- Cooperative tasks --\n";
    // scheduler.schedule(task_a("A", 3).handle());  // pseudocode — implement properly
    // scheduler.schedule(task_a("B", 3).handle());
    // scheduler.run();

    // TODO: Schedule outer_task() and run. Print the computed result.
    std::cout << "\n-- Chained task --\n";

    // TODO: Schedule the exception-handling wrapper and run.
    std::cout << "\n-- Exception in coroutine --\n";

    return 0;
}
