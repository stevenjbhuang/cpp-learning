/*
 * ============================================================
 * Module 13 — Concurrency Basics (C++17)
 * ============================================================
 *
 * C++ provides portable concurrency primitives in <thread>,
 * <mutex>, <condition_variable>, and <future>. These map
 * closely to OS threads and are the foundation for the
 * higher-level constructs in later modules.
 *
 * Key concepts:
 *
 * 1. std::thread
 *    - Represents a single OS thread
 *    - Constructor takes a callable + arguments (copies/moves them)
 *    - Must call join() or detach() before destruction, else std::terminate()
 *    - std::jthread (C++20): automatically joins on destruction
 *    - thread_local: each thread has its own copy of the variable
 *
 * 2. Data races & undefined behaviour
 *    - A data race occurs when two threads access the same memory location
 *      concurrently and at least one is a write, without synchronisation
 *    - Data races are undefined behaviour — the program is wrong, not just slow
 *
 * 3. std::mutex
 *    - Mutual exclusion lock: only one thread holds it at a time
 *    - lock() / unlock() — manual management (error-prone)
 *    - std::lock_guard<std::mutex>: RAII wrapper, unlocks on scope exit
 *    - std::unique_lock<std::mutex>: like lock_guard but movable and re-lockable
 *    - std::scoped_lock (C++17): lock multiple mutexes atomically (avoids deadlock)
 *
 * 4. std::condition_variable
 *    - Allows threads to wait for a condition to become true
 *    - wait(unique_lock, predicate): atomically releases lock and sleeps
 *    - notify_one() / notify_all(): wake sleeping threads
 *    - Always use a predicate to guard against spurious wakeups
 *
 * 5. std::future / std::promise
 *    - One-shot channel for passing a value from one thread to another
 *    - std::async: launch a callable asynchronously; returns a future
 *    - future.get(): blocks until the result is ready; re-throws exceptions
 *    - std::launch::async vs std::launch::deferred
 *
 * 6. Deadlock avoidance
 *    - Always lock mutexes in a consistent order across all threads
 *    - Prefer std::scoped_lock over manual lock ordering
 *    - Keep critical sections short
 *
 * Build & run:
 *   make run MODULE=13_concurrency_basics
 * ============================================================
 */

#include <chrono>
#include <condition_variable>
#include <future>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

// ── 1. Basic thread creation ──────────────────────────────────────────────────
void demo_threads() {
    // TODO: Spawn 4 threads, each printing its thread number.
    //       Join all threads before returning.
    //       Observe that the print order is non-deterministic.

    // TODO: Pass arguments to threads: each thread computes and prints square(i)
    //       for i in 1..4.

    // TODO: Use thread_local int call_count = 0; inside a function.
    //       Spawn two threads that each call the function 3 times.
    //       Show each thread has its own counter.
}

// ── 2. Mutex & data race ──────────────────────────────────────────────────────
void demo_mutex() {
    int shared_counter = 0;
    std::mutex mtx;

    // TODO: Spawn 10 threads, each incrementing shared_counter 1000 times.
    //       First do it WITHOUT a mutex — observe the race condition result.
    //       Then add a lock_guard inside the loop — result should be 10000.

    // TODO: Replace lock_guard with unique_lock. Show how to manually unlock
    //       early to reduce the critical section.
}

// ── 3. condition_variable — producer/consumer ─────────────────────────────────
void demo_condition_variable() {
    std::mutex mtx;
    std::condition_variable cv;
    std::vector<int> work_queue;
    bool done = false;

    // TODO: Consumer thread:
    //   - Lock, wait on cv until queue is non-empty OR done is true
    //   - Process (print) all items in the queue
    //   - Loop until done && queue is empty

    // TODO: Producer (main thread or separate thread):
    //   - Lock, push items {1..5} one at a time with a small sleep
    //   - notify_one() after each push
    //   - After pushing all, set done=true and notify_all()

    // TODO: Join the consumer thread.
}

// ── 4. std::async / std::future ──────────────────────────────────────────────
void demo_async() {
    // TODO: Launch a slow computation with std::async(std::launch::async, ...)
    //       that sleeps 100ms and returns a double.
    //       Do other work while it runs, then get() the result.

    // TODO: Launch multiple async tasks (parallel map):
    //         vector of futures, each computing square root of a number.
    //       Collect results by calling .get() on each.

    // TODO: Demonstrate exception propagation: async task that throws;
    //       catch the exception at future.get().
}

// ── 5. scoped_lock — avoid deadlock ──────────────────────────────────────────
void demo_scoped_lock() {
    std::mutex m1, m2;
    int resource_a = 0, resource_b = 0;

    // TODO: Spawn two threads that both need to lock m1 and m2.
    //       Thread 1: locks m1 then m2.
    //       Thread 2: locks m2 then m1.
    //       WITHOUT scoped_lock this can deadlock — demonstrate with a comment.
    //
    // TODO: Fix by using std::scoped_lock(m1, m2) in both threads.
    //       Both modify resource_a and resource_b, then print.
}

int main() {
    std::cout << "=== 13: Concurrency Basics ===\n\n";

    std::cout << "-- Thread creation --\n";   demo_threads();
    std::cout << "\n-- Mutex --\n";             demo_mutex();
    std::cout << "\n-- condition_variable --\n"; demo_condition_variable();
    std::cout << "\n-- async/future --\n";      demo_async();
    std::cout << "\n-- scoped_lock --\n";       demo_scoped_lock();

    return 0;
}
