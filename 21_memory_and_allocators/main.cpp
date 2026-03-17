/*
 * ============================================================
 * Module 21 — Memory & Custom Allocators (C++17)
 * ============================================================
 *
 * Memory allocation is one of the most significant sources of
 * latency jitter in high-performance systems. Custom allocators
 * let you eliminate heap fragmentation, reduce lock contention,
 * and improve cache locality by controlling exactly when and
 * how memory is obtained.
 *
 * Key concepts:
 *
 * 1. Placement new
 *    - Constructs an object in pre-allocated storage
 *    - Syntax: new (ptr) T(args...);
 *    - Must manually call the destructor: ptr->~T();
 *    - Foundation of object pools, arenas, and in-place std::optional
 *
 * 2. Memory alignment
 *    - Misaligned access is UB on strict-alignment architectures
 *    - alignas(N): specifier to align a variable or type
 *    - alignof(T): query the alignment requirement of T
 *    - std::align(alignment, size, ptr, space): align a pointer in a buffer
 *    - Aligned allocation: aligned_alloc / operator new(size, std::align_val_t)
 *
 * 3. Linear (arena) allocator
 *    - Bump-pointer allocation: O(1) alloc, zero-cost free (bulk free only)
 *    - All objects share a lifetime: free the entire arena at once
 *    - Ideal for per-frame allocations in game loops and per-request allocations
 *      in servers
 *
 * 4. Pool allocator
 *    - Fixed-size block allocator: O(1) alloc and free
 *    - Free list of same-size blocks; push/pop on free/alloc
 *    - Eliminates fragmentation for uniform-size objects
 *    - Used for message queues, packet buffers, task objects
 *
 * 5. PMR — Polymorphic Memory Resources (<memory_resource>, C++17)
 *    - std::pmr::memory_resource: abstract base with do_allocate/do_deallocate
 *    - std::pmr::monotonic_buffer_resource: arena on a fixed buffer
 *    - std::pmr::unsynchronized_pool_resource: pool without locking
 *    - std::pmr::synchronized_pool_resource: thread-safe pool
 *    - std::pmr::vector<T>, std::pmr::string: PMR-aware container aliases
 *    - Use std::pmr::get_default_resource() / set_default_resource()
 *
 * 6. std::allocator_traits
 *    - Uniform interface for allocator operations
 *    - Allows containers to work with any allocator type
 *    - Required if writing a custom STL-compatible allocator
 *
 * Build & run:
 *   make run MODULE=21_memory_and_allocators
 * ============================================================
 */

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <memory_resource>
#include <new>
#include <string>
#include <vector>

// ── 1. Placement new ─────────────────────────────────────────────────────────
void demo_placement_new() {
    // TODO: Allocate a raw byte buffer aligned for std::string:
    //         alignas(std::string) std::byte buf[sizeof(std::string)];
    // TODO: Construct a std::string in buf using placement new.
    // TODO: Use the string (assign, print).
    // TODO: Explicitly destroy it: std::destroy_at(ptr) or ptr->~string().
    // TODO: In comments, explain why you must NOT call delete on a placement-new ptr.
}

// ── 2. Linear (arena) allocator ──────────────────────────────────────────────
// TODO: Implement class ArenaAllocator:
//
//   ArenaAllocator(std::size_t capacity)  — allocates a char[] backing buffer
//   void* allocate(std::size_t size, std::size_t align = alignof(std::max_align_t))
//     — bump the offset; use std::align to respect alignment; return nullptr if full
//   void reset()  — sets offset back to 0 (all objects implicitly "freed")
//   std::size_t used() const
//   std::size_t capacity() const
//   ~ArenaAllocator()  — frees the backing buffer

void demo_arena() {
    // TODO: Create ArenaAllocator(1024).
    // TODO: Allocate space for 3 ints with placement new. Assign values.
    // TODO: Allocate space for a double (mind the alignment).
    // TODO: Print used() before and after reset().
}

// ── 3. Pool allocator ─────────────────────────────────────────────────────────
// TODO: Implement template <typename T, std::size_t BlockCount> class PoolAllocator:
//
//   Pre-allocates BlockCount * sizeof(T) bytes in a flat buffer.
//   Free list: a singly linked list of available blocks threaded through the buffer.
//
//   T* allocate()    — pop from free list; return nullptr if exhausted
//   void deallocate(T* ptr) — push back onto free list
//   std::size_t available() const

struct Packet {
    uint8_t data[64];
    uint32_t seq;
};

void demo_pool() {
    // TODO: PoolAllocator<Packet, 8> pool;
    // TODO: Allocate 4 packets, assign seq numbers.
    // TODO: Deallocate 2, allocate 2 more.
    // TODO: Print available() after each operation.
}

// ── 4. PMR — monotonic_buffer_resource ───────────────────────────────────────
void demo_pmr_monotonic() {
    // TODO: Allocate a 4096-byte stack buffer.
    // TODO: Construct std::pmr::monotonic_buffer_resource from it.
    // TODO: Create std::pmr::vector<int> and std::pmr::string using the resource.
    //       Append elements; they should not touch the global heap.
    // TODO: Print &resource and the addresses of vector data — both in the buffer.
}

// ── 5. PMR — pool resource ────────────────────────────────────────────────────
void demo_pmr_pool() {
    // TODO: Create std::pmr::unsynchronized_pool_resource (backed by new_delete_resource).
    // TODO: Allocate several std::pmr::vector<std::string> instances using it.
    //       Watch how multiple small allocations are pooled.
    // TODO: Print resource.pool_options() if available, or comment on configuration.
}

int main() {
    std::cout << "=== 21: Memory & Allocators ===\n\n";

    std::cout << "-- Placement new --\n";    demo_placement_new();
    std::cout << "\n-- Arena --\n";           demo_arena();
    std::cout << "\n-- Pool --\n";            demo_pool();
    std::cout << "\n-- PMR monotonic --\n";   demo_pmr_monotonic();
    std::cout << "\n-- PMR pool --\n";        demo_pmr_pool();

    return 0;
}
