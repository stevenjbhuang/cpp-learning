/*
 * ============================================================
 * Module 19 — Custom Data Structures (C++17)
 * ============================================================
 *
 * Implementing data structures from scratch deepens your
 * understanding of memory layout, iterator design, and
 * algorithmic complexity. These hand-rolled versions can
 * also be tuned to specific workloads in a way that generic
 * library containers cannot.
 *
 * Key concepts:
 *
 * 1. Intrusive linked list
 *    - The node pointer is stored inside the data object itself
 *    - No separate heap allocation per element — better cache behaviour
 *    - Used in OS kernels, real-time systems, and high-performance software
 *    - The list does NOT own the objects; the caller manages lifetime
 *
 * 2. Open-addressing hash map
 *    - All entries live in a single flat array — excellent cache locality
 *    - Linear probing: on collision, walk forward to find an empty slot
 *    - Load factor: keep < 0.75 to bound probe chains
 *    - Tombstone deletion or robin-hood hashing for erase support
 *
 * 3. Min-heap / priority queue
 *    - Complete binary tree stored in a flat array
 *    - Parent at index i; children at 2i+1 and 2i+2
 *    - Push: append + sift up; Pop: swap root with last + sift down
 *    - O(log n) push and pop; O(1) peek

 * 4. Circular buffer (ring buffer)
 *    - Fixed-capacity FIFO queue in a flat array
 *    - head and tail indices wrap with modulo
 *    - O(1) push and pop; no dynamic allocation after construction
 *    - Building block for lock-free single-producer/single-consumer queues
 *
 * 5. Trie (prefix tree)
 *    - Stores strings as paths from root to leaf
 *    - O(L) insert/search where L = string length (independent of n)
 *    - Autocomplete, dictionary compression, IP routing tables
 *
 * Build & run:
 *   make run MODULE=19_data_structures
 * ============================================================
 */

#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

// ── 1. Intrusive doubly-linked list ──────────────────────────────────────────
// TODO: Define struct IntrusiveNode { IntrusiveNode *prev{}, *next{}; };
//
// TODO: Implement class IntrusiveList (does NOT own nodes):
//   - void push_back(IntrusiveNode* node)
//   - void remove(IntrusiveNode* node)
//   - void for_each(std::function<void(IntrusiveNode*)> fn) const
//   - std::size_t size() const
//
// TODO: Create a struct Task : IntrusiveNode { std::string name; int priority; };
//       Add several Tasks to the list and iterate them.

// ── 2. Open-addressing hash map ───────────────────────────────────────────────
// TODO: Implement template <typename K, typename V, std::size_t Capacity>
//       class FlatHashMap:
//
//   Internal state:
//     struct Slot { std::optional<K> key; V value; };
//     std::array<Slot, Capacity> table_{};
//
//   Operations:
//     void insert(const K& k, V v)         — linear probe on collision
//     std::optional<V> find(const K& k) const
//     bool erase(const K& k)               — tombstone: set key = nullopt + mark
//     float load_factor() const
//
//   Hash: use std::hash<K>{}(k) % Capacity as starting index.
//   NOTE: For simplicity, skip the tombstone complexity — just mark the slot
//         as deleted and handle it during insert/find.

// ── 3. Min-heap ───────────────────────────────────────────────────────────────
// TODO: Implement template <typename T, typename Compare = std::less<T>>
//       class MinHeap:
//
//     void push(T val)
//     T    pop()               — returns and removes the minimum
//     const T& top() const
//     bool empty() const
//     std::size_t size() const
//
//   Use std::vector<T> as the backing store.
//   sift_up(i): while i > 0 && parent(i) > data[i]: swap, move to parent
//   sift_down(i): while child(i) < data[i]: swap with smaller child, move down

// ── 4. Circular buffer ────────────────────────────────────────────────────────
// TODO: Implement template <typename T, std::size_t N> class CircularBuffer:
//
//     bool push(const T& val)   — returns false if full
//     std::optional<T> pop()    — returns nullopt if empty
//     bool full() const
//     bool empty() const
//     std::size_t size() const
//
//   Use std::array<T,N> backing storage.
//   head_ points to the next read, tail_ points to the next write.
//   size_ tracks element count to distinguish full from empty.

// ── 5. Trie ───────────────────────────────────────────────────────────────────
// TODO: Implement a 26-ary Trie (lowercase ASCII letters only):
//
//   struct TrieNode {
//     std::array<TrieNode*, 26> children{};
//     bool is_end{false};
//   };
//
//   class Trie {
//     TrieNode root_;
//   public:
//     void insert(std::string_view word);
//     bool search(std::string_view word) const;
//     bool starts_with(std::string_view prefix) const;
//     void print_all(std::string_view prefix = "") const;  // DFS
//   };
//
//   NOTE: For simplicity, use owning raw pointers (new/delete) or
//         std::unique_ptr<TrieNode> in the children array.

int main() {
    std::cout << "=== 19: Custom Data Structures ===\n\n";

    std::cout << "-- Intrusive list --\n";
    // TODO: Create Task objects, insert into IntrusiveList, iterate and print.
    // TODO: Remove one task and verify.

    std::cout << "\n-- FlatHashMap --\n";
    // TODO: FlatHashMap<std::string, int, 16> map;
    //       insert("a",1), ("b",2), ("c",3). find("b"). erase("a"). find("a").

    std::cout << "\n-- MinHeap --\n";
    // TODO: Push {5,3,8,1,9,2}. Pop all; should come out sorted ascending.

    std::cout << "\n-- CircularBuffer --\n";
    // TODO: CircularBuffer<int,4>: push 1..4, verify full(), pop 2, push 5, print all.

    std::cout << "\n-- Trie --\n";
    // TODO: Insert "cat","car","card","care","dog". Search "car" and "bus".
    //       starts_with("car"). print_all() to show dictionary.

    return 0;
}
