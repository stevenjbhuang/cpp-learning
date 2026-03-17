/*
 * ============================================================
 * Module 10 — Move Semantics & Value Categories (C++17)
 * ============================================================
 *
 * Move semantics allow resources to be transferred rather than
 * copied, eliminating unnecessary allocations on the hot path.
 * Understanding value categories (lvalue/rvalue) is essential
 * for writing efficient modern C++.
 *
 * Key concepts:
 *
 * 1. Value categories
 *    - lvalue  : has an address; can appear on the left of an assignment
 *    - rvalue  : temporary or about-to-expire value; no persistent address
 *    - xvalue  : "expiring value" — result of std::move(); lvalue cast to rvalue
 *    - glvalue : generalised lvalue (lvalue + xvalue)
 *    - prvalue : pure rvalue (literal, function return value not a reference)
 *
 * 2. Move constructor & move assignment
 *    - Take an rvalue reference (T&&)
 *    - Steal resources from the source; leave source in a valid-but-unspecified state
 *    - Mark noexcept to allow STL containers to use them during reallocation
 *    - Compiler generates them if no user-declared Rule-of-Five members exist
 *
 * 3. std::move
 *    - Cast an lvalue to an rvalue reference: `static_cast<T&&>(x)`
 *    - Does NOT move anything by itself — just changes the value category
 *    - After std::move(x), do not use x again (unless you reset it)
 *
 * 4. Perfect forwarding & std::forward
 *    - Forwarding references: `template<typename T> void f(T&& arg)`
 *    - `T&&` in a template deduces to lvalue ref if called with lvalue,
 *      rvalue ref if called with rvalue (reference collapsing rules)
 *    - std::forward<T>(arg) restores the original value category
 *    - Pattern: factory functions, wrapper functions (emplace, make_unique)
 *
 * 5. Return Value Optimisation (RVO / NRVO)
 *    - Compiler constructs the return value directly in the caller's storage
 *    - No copy or move needed — elision is mandatory for prvalues in C++17
 *    - Do NOT std::move a local variable you are returning — it defeats RVO
 *
 * 6. Move-only types
 *    - Types where copy is deleted but move is defined
 *    - Examples: std::unique_ptr, std::thread, std::fstream
 *    - Pass by value when the function takes ownership; forward otherwise
 *
 * Build & run:
 *   make run MODULE=10_move_semantics
 * ============================================================
 */

#include <iostream>
#include <string>
#include <utility>
#include <vector>

// ── 1. Instrument a class to observe move vs copy ─────────────────────────────
// TODO: Implement class Tensor with:
//   - A std::string name_ and std::vector<float> data_ member
//   - Constructor: Tensor(std::string name, std::size_t size)
//     fills data_ with size floats (use std::iota or any values)
//   - Copy constructor/assignment: print "[Tensor] copy <name>"
//   - Move constructor/assignment (noexcept): print "[Tensor] move <name>"
//   - Destructor: print "[Tensor] ~<name>"
//   - Accessor: const std::string& name() const; std::size_t size() const

// ── 2. Demonstrate move vs copy ───────────────────────────────────────────────
void demo_move_vs_copy() {
    // TODO: Create Tensor t1("weights", 1000).
    // TODO: Copy-construct t2 from t1. Observe the copy message.
    // TODO: Move-construct t3 from t1 using std::move. Observe the move message.
    //       Print t1.size() — what is it after the move?
    // TODO: Move-assign a new Tensor into t2.
}

// ── 3. std::move in containers ────────────────────────────────────────────────
void demo_move_in_vector() {
    std::vector<Tensor> tensors;
    tensors.reserve(3);  // prevent reallocation to isolate messages

    // TODO: push_back a copy of a Tensor, then push_back using std::move.
    //       Observe the difference in constructor calls.
    // TODO: emplace_back with constructor arguments directly.
    //       Note: emplace_back constructs in-place — zero move/copy.
}

// ── 4. Perfect forwarding ─────────────────────────────────────────────────────
// TODO: Implement a factory function:
//   template <typename T, typename... Args>
//   T make(Args&&... args) {
//       return T(std::forward<Args>(args)...);
//   }
//
// TODO: Call make<Tensor>("via_factory", 256) and observe that no extra
//       move/copy occurs (RVO applies).

// ── 5. Forwarding reference vs rvalue reference ───────────────────────────────
// TODO: Write two overloaded functions:
//   void process(Tensor& t)  — prints "lvalue"
//   void process(Tensor&& t) — prints "rvalue"
//
// TODO: Write `template <typename T> void relay(T&& t) { process(std::forward<T>(t)); }`
//
// Demonstrate:
//   Tensor t("relay_test", 4);
//   relay(t);             // should call lvalue overload
//   relay(std::move(t));  // should call rvalue overload

// ── 6. Move-only type ────────────────────────────────────────────────────────
// TODO: Implement class UniqueHandle:
//   - Wraps an int (simulating a file descriptor / OS handle)
//   - Constructor: explicit UniqueHandle(int fd)
//   - Destructor: prints "closing handle <fd>"
//   - Move-only: delete copy, implement move (set moved-from fd to -1)
//   - Accessor: int get() const

void demo_move_only() {
    // TODO: Create two UniqueHandles and move one into a vector.
    //       Show that copying is a compile error (comment it out).
    // TODO: Transfer ownership via std::move and verify the source is invalidated.
}

int main() {
    std::cout << "=== 10: Move Semantics ===\n\n";

    std::cout << "-- Move vs Copy --\n";   demo_move_vs_copy();
    std::cout << "\n-- Move in vector --\n"; demo_move_in_vector();
    std::cout << "\n-- Perfect forwarding --\n";
    // TODO: Call make<Tensor>, relay lvalue, relay rvalue.
    std::cout << "\n-- Move-only --\n";     demo_move_only();

    return 0;
}
