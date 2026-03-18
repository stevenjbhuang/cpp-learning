/*
 * ============================================================
 * Module 11 — Smart Pointers (C++17)
 * ============================================================
 *
 * Smart pointers are RAII wrappers around raw pointers that
 * automate memory management. They eliminate the most common
 * category of C++ bugs: use-after-free, double-free, and leaks.
 *
 * Key concepts:
 *
 * 1. std::unique_ptr<T>
 *    - Single ownership: exactly one unique_ptr owns the pointee
 *    - Move-only: transferring ownership via std::move
 *    - Zero overhead over a raw pointer in most compilers
 *    - make_unique<T>(args...) — preferred construction (exception-safe)
 *    - Custom deleter: unique_ptr<T, Deleter>
 *    - release() — give up ownership; get() — observe without owning
 *
 * 2. std::shared_ptr<T>
 *    - Shared ownership: reference-counted
 *    - Copies increment the ref count; destructor decrements it
 *    - make_shared<T> — single allocation for object + control block
 *    - Thread-safe ref-count manipulation (but not the pointed-to object!)
 *    - Overhead: two words (pointer + control block pointer)
 *
 * 3. std::weak_ptr<T>
 *    - Non-owning observer of a shared_ptr-managed object
 *    - Does not prevent destruction; must lock() to get a shared_ptr
 *    - Use to break reference cycles that would leak memory
 *    - Check expired() before locking, or check the locked shared_ptr
 *
 * 4. Custom deleters
 *    - unique_ptr<T, Deleter> and shared_ptr<T> both accept a deleter
 *    - Use for resources that are not heap memory:
 *        file descriptors, sockets, GPU buffers, C library handles
 *
 * 5. enable_shared_from_this
 *    - Allows a class to safely produce a shared_ptr to itself
 *    - Inherit: class Foo : public std::enable_shared_from_this<Foo>
 *    - Call shared_from_this() — only valid if already managed by a shared_ptr
 *    - Never construct shared_ptr<T>(this) directly
 *
 * 6. When to use which
 *    - unique_ptr: default for single-owner heap objects
 *    - shared_ptr: genuinely shared lifetime (trees, graphs, caches)
 *    - weak_ptr:   back-pointers, observer pattern, cache entries
 *    - Raw pointer / reference: non-owning access when lifetime is guaranteed
 *
 * Build & run:
 *   make run MODULE=11_smart_pointers
 * ============================================================
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ── Instrumented class to observe construction/destruction ────────────────────
struct Resource {
    std::string name;
    explicit Resource(std::string n) : name(std::move(n)) {
        std::cout << "[Resource] created: " << name << "\n";
    }
    ~Resource() { std::cout << "[Resource] destroyed: " << name << "\n"; }
};

// ── 1. unique_ptr ─────────────────────────────────────────────────────────────
void demo_unique_ptr() {
    // TODO: Create a unique_ptr<Resource> using make_unique. Print the name.
    // TODO: Transfer ownership with std::move into a second unique_ptr.
    //       Show the original is now null (operator bool, or == nullptr).
    // TODO: Return a unique_ptr from a lambda (verify RVO — no extra moves).
    // TODO: Create a unique_ptr with a custom deleter (a lambda that prints
    //       "custom delete" before releasing). Wrap a raw pointer.
    // TODO: unique_ptr<Resource[]> for array ownership. Access elements with [].
}

// ── 2. shared_ptr ────────────────────────────────────────────────────────────
void demo_shared_ptr() {
    // TODO: Create a shared_ptr<Resource> with make_shared.
    // TODO: Copy it; print use_count() — should be 2.
    // TODO: Reset one copy; print use_count() — should be 1.
    // TODO: Store shared_ptrs to base class in a vector<shared_ptr<Base>>
    //       and add derived objects (demonstrate polymorphism still works).
    // TODO: Print use_count() after the vector goes out of scope.
}

// ── 3. weak_ptr & cycle breaking ─────────────────────────────────────────────
// TODO: Implement a Node struct for a doubly-linked demo:
//   struct Node {
//     std::string name;
//     std::shared_ptr<Node> next;
//     std::weak_ptr<Node>   prev;   // weak to avoid cycle
//     explicit Node(std::string n);
//     ~Node();
//   };

void demo_weak_ptr() {
    // TODO: Create Node "A" and Node "B" as shared_ptrs.
    //       Set A->next = B, B->prev = A (weak_ptr — no cycle).
    // TODO: Show that all Nodes are destroyed when shared_ptrs leave scope.
    //       (For comparison, briefly explain what happens if both links are
    //        shared_ptr — memory leaks. No need to implement it.)
    // TODO: Lock a weak_ptr and use the resulting shared_ptr safely.
    //       Check expired() after the owning shared_ptr is reset.
}

// ── 4. enable_shared_from_this ───────────────────────────────────────────────
// TODO: Implement class EventEmitter : public std::enable_shared_from_this<EventEmitter>
//   - void subscribe(std::shared_ptr<EventEmitter> listener)
//     stores listener in a vector
//   - void emit() calls a virtual on each listener
//   - void register_self() calls subscribe(shared_from_this())
//       — show this is safe only when managed by a shared_ptr

void demo_enable_shared() {
    // TODO: Make an EventEmitter via make_shared, call register_self().
    // TODO: Show that calling shared_from_this() on a stack object throws
    //       std::bad_weak_ptr (wrap in try/catch).
}

int main() {
    std::cout << "=== 11: Smart Pointers ===\n\n";

    std::cout << "-- unique_ptr --\n";   demo_unique_ptr();
    std::cout << "\n-- shared_ptr --\n";  demo_shared_ptr();
    std::cout << "\n-- weak_ptr --\n";    demo_weak_ptr();
    std::cout << "\n-- enable_shared_from_this --\n"; demo_enable_shared();

    return 0;
}
