/*
 * ============================================================
 * Module 03 — Pointers & References (C++17)
 * ============================================================
 *
 * Pointers and references are the foundation of C++ memory
 * management, aliasing, and zero-cost abstraction. This module
 * builds the mental model needed for smart pointers, iterators,
 * and low-level system programming.
 *
 * Key concepts:
 *
 * 1. Pointer basics
 *    - A pointer stores the address of another object
 *    - Operators: & (address-of), * (dereference)
 *    - nullptr: the null pointer constant — always prefer over NULL or 0
 *    - Pointer-to-pointer: int**
 *    - Always initialise pointers (to nullptr if not yet valid)
 *
 * 2. Pointer arithmetic
 *    - Adding/subtracting integers moves by sizeof(T)
 *    - Pointer difference gives element count between two pointers
 *    - Undefined behaviour: out-of-bounds access, pointer from freed memory
 *
 * 3. References
 *    - An alias for an existing object; cannot be null, cannot be reseated
 *    - Pass-by-reference avoids copies for large types
 *    - Returning a reference: caller can assign through it
 *    - Danger: never return a reference to a local variable
 *
 * 4. const correctness
 *    - `const int* p`      — pointer to const int (value immutable)
 *    - `int* const p`      — const pointer (address immutable)
 *    - `const int* const p` — both immutable
 *    - `const T&` in function parameters: read-only, no copy
 *    - const member functions: promise not to modify the object
 *
 * 5. std::span (C++20, widely available)
 *    - Non-owning view over a contiguous sequence (array, vector, etc.)
 *    - Safer than raw pointer+size pairs
 *    - std::span<const T> for read-only views
 *    - Subspan: span.subspan(offset, count)
 *
 * 6. void* and type-safe casting
 *    - void* can hold any pointer but cannot be dereferenced directly
 *    - Must static_cast back to the original type before use
 *    - In modern C++, prefer std::any or templates over void*
 *
 * Build & run:
 *   make run MODULE=03_pointers_and_references
 * ============================================================
 */

#include <iostream>
#include <span>
#include <string>
#include <vector>

// ── 1. Pointer basics ────────────────────────────────────────────────────────
void demo_pointers() {
    // TODO: Declare an int and a pointer to it. Modify the int through the pointer.
    // TODO: Declare a pointer-to-pointer (int**) and modify the int through it.
    // TODO: Declare a null pointer and check it before dereferencing.
    // TODO: Print the address stored in the pointer using the %p format or <<.
}

// ── 2. Pointer arithmetic ────────────────────────────────────────────────────
void demo_pointer_arithmetic() {
    int arr[5] = {10, 20, 30, 40, 50};

    // TODO: Use a pointer starting at arr[0] and iterate the array using *(p+i).
    // TODO: Walk the array with ++p in a loop until you reach arr+5.
    // TODO: Compute and print the difference between two element pointers.
}

// ── 3. References ────────────────────────────────────────────────────────────
// TODO: Write `void increment(int& val)` that increments val in-place.
// TODO: Write `int& get_first(int* arr)` that returns a reference to arr[0].
//       Use it on the left-hand side of an assignment in main.

void demo_references() {
    // TODO: Call increment() and verify the original variable changed.
    // TODO: Use get_first() to set arr[0] to 99 and verify.
}

// ── 4. const correctness ─────────────────────────────────────────────────────
void demo_const_correctness() {
    int a = 1, b = 2;

    // TODO: Declare `const int* ptr_to_const` pointing to a.
    //       Try reassigning the pointer to &b (OK).
    //       Show (as a comment) what compile error happens if you write *ptr_to_const = 99.

    // TODO: Declare `int* const const_ptr` pointing to a.
    //       Modify *const_ptr (OK).
    //       Show (as a comment) what compile error happens if you try const_ptr = &b.

    // TODO: Declare `const int* const both_const` — neither can change.

    // TODO: Take a large std::string by `const std::string&` in a local lambda
    //       and verify no copy is made (add a comment explaining why).
}

// ── 5. std::span — non-owning view ───────────────────────────────────────────
// TODO: Write `double sum(std::span<const double> data)` that sums elements.
//       Call it with a raw array, a std::vector<double>, and a subspan.

void demo_span() {
    double arr[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> vec = {10.0, 20.0, 30.0};

    // TODO: Print the sum of arr, then vec, then a subspan of arr (indices 1..3).
    // TODO: Modify elements through a non-const span and verify the change.
}

// ── 6. void* and type-safe casting ───────────────────────────────────────────
void demo_void_ptr() {
    // TODO: Assign an int* to a void*, then recover it with static_cast<int*>.
    //       Print the recovered value.
    // TODO: In a comment, explain why reinterpret_cast is dangerous here and
    //       static_cast is preferred when the original type is known.
}

int main() {
    std::cout << "=== 03: Pointers & References ===\n\n";

    std::cout << "-- Pointer basics --\n";
    demo_pointers();

    std::cout << "\n-- Pointer arithmetic --\n";
    demo_pointer_arithmetic();

    std::cout << "\n-- References --\n";
    demo_references();

    std::cout << "\n-- const correctness --\n";
    demo_const_correctness();

    std::cout << "\n-- std::span --\n";
    demo_span();

    std::cout << "\n-- void* --\n";
    demo_void_ptr();

    return 0;
}
