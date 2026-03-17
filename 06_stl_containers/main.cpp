/*
 * ============================================================
 * Module 06 — STL Containers (C++17)
 * ============================================================
 *
 * The Standard Library containers provide ready-made data
 * structures with well-defined complexity guarantees. Choosing
 * the right container for the job is one of the most impactful
 * performance decisions you can make.
 *
 * Key concepts:
 *
 * 1. std::vector — dynamic array
 *    - O(1) amortised push_back, O(1) random access
 *    - Contiguous memory → excellent cache locality
 *    - reserve() to avoid reallocations; shrink_to_fit() to release
 *    - erase() is O(n) due to element shifting
 *
 * 2. std::deque — double-ended queue
 *    - O(1) push_front and push_back (unlike vector)
 *    - Not contiguous; slightly worse cache behaviour than vector
 *    - Use when you need fast insertion at both ends
 *
 * 3. std::list — doubly-linked list
 *    - O(1) insert/erase anywhere given an iterator
 *    - No random access; O(n) to reach element i
 *    - splice() moves nodes between lists in O(1)
 *    - Consider only when you have many mid-sequence insertions/deletions
 *
 * 4. std::map — sorted key-value (red-black tree)
 *    - O(log n) insert, find, erase
 *    - Iterating in key order
 *    - operator[] inserts a default-constructed value if key is absent
 *    - Prefer find() for safe lookup; at() throws on missing key
 *
 * 5. std::unordered_map — hash map
 *    - O(1) average insert/find/erase; O(n) worst case
 *    - reserve() to pre-size the bucket array and avoid rehashing
 *    - Custom hash required for user-defined key types
 *
 * 6. std::set / std::unordered_set
 *    - Unique elements only; duplicates are silently ignored
 *    - set: sorted, O(log n); unordered_set: hash-based, O(1) avg
 *
 * 7. std::array — fixed-size, stack-allocated
 *    - Size is a compile-time constant; zero overhead vs raw array
 *    - Supports STL algorithms; has .size(), .begin(), .end()
 *
 * 8. std::stack / std::queue — container adaptors
 *    - stack: LIFO (backed by deque by default)
 *    - queue: FIFO (backed by deque by default)
 *    - priority_queue: max-heap by default
 *
 * Container Selection Guide:
 * ─────────────────────────────────────────────────────────────────────────
 * │ Need                        │ Container              │ Note            │
 * ├─────────────────────────────┼────────────────────────┼─────────────────┤
 * │ Random access + fast append │ vector                 │ default choice  │
 * │ Fast front/back insert      │ deque                  │                 │
 * │ O(1) insert/erase anywhere  │ list / forward_list    │ no random access│
 * │ Sorted key-value            │ map / multimap         │ O(log n)        │
 * │ Fast key-value lookup       │ unordered_map          │ O(1) avg        │
 * │ Sorted unique values        │ set / multiset         │                 │
 * │ Fast membership test        │ unordered_set          │                 │
 * │ Fixed size, stack allocated │ array                  │ zero overhead   │
 * │ LIFO access                 │ stack (adaptor)        │                 │
 * │ FIFO access                 │ queue (adaptor)        │                 │
 * │ Priority-ordered access     │ priority_queue         │                 │
 * ─────────────────────────────────────────────────────────────────────────
 *
 * Build & run:
 *   make run MODULE=06_stl_containers
 * ============================================================
 */

#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// ── 1. std::vector ────────────────────────────────────────────────────────────
void demo_vector() {
    // TODO: Create vector<int> with initialiser list {3,1,4,1,5,9}.
    // TODO: push_back a new element, then reserve(20).
    //       Print size and capacity — notice capacity jumps but size does not.
    // TODO: Erase the element at index 1 using v.begin()+1. Print the result.
    // TODO: Try emplace_back vs push_back and explain the difference in a comment.
}

// ── 2. std::deque ────────────────────────────────────────────────────────────
void demo_deque() {
    // TODO: Create deque<int> {3,4,5}. Push 2 and 1 to the front, 6 to the back.
    //       Print all elements.
    // TODO: pop_front() and pop_back() once each. Print remaining elements.
}

// ── 3. std::list ─────────────────────────────────────────────────────────────
void demo_list() {
    // TODO: Create list<int> {1,3,5,7}.
    // TODO: Insert 4 before the element 5 using an iterator (std::next).
    // TODO: Call remove(3) to erase all 3s. Print the list.
    // TODO: Create a second list and splice its elements into the first. Print.
}

// ── 4. std::map ──────────────────────────────────────────────────────────────
void demo_map() {
    // TODO: Create map<string, double> with sensor names and values.
    // TODO: Insert a new entry with operator[].
    //       Explain in a comment what happens if the key is new vs existing.
    // TODO: Iterate with structured bindings: for (const auto& [k,v] : m).
    // TODO: Use find() for safe lookup. Show the difference from at().
}

// ── 5. std::unordered_map ────────────────────────────────────────────────────
void demo_unordered_map() {
    // TODO: Create unordered_map<int, string>, call reserve(100).
    // TODO: Insert three entries, then access one with at().
    // TODO: Print load_factor() before and after reserve. Explain what it means.
}

// ── 6. std::set / unordered_set ──────────────────────────────────────────────
void demo_sets() {
    // TODO: Create set<int> with values including duplicates.
    //       Print all values — observe sorted order and no duplicates.
    // TODO: insert() a duplicate. Check the returned pair<iterator,bool>.
    // TODO: Create unordered_set<string>. Insert duplicate; print size.
}

// ── 7. std::array ────────────────────────────────────────────────────────────
void demo_array() {
    // TODO: Declare array<double, 6> for joint angles.
    // TODO: Print size, first, and last element using front() and back().
    // TODO: Sort it with std::sort and print again.
}

// ── 8. std::stack, std::queue, std::priority_queue ───────────────────────────
void demo_adaptors() {
    // TODO: Push three ints onto a stack. Print top and observe LIFO by popping.
    // TODO: Push three strings into a queue. Print front and observe FIFO.
    // TODO: Create a priority_queue<int> and push {3,1,4,1,5,9}.
    //       Pop all and print — elements should come out in descending order.
}

int main() {
    std::cout << "=== 06: STL Containers ===\n\n";

    std::cout << "-- vector --\n";    demo_vector();
    std::cout << "\n-- deque --\n";   demo_deque();
    std::cout << "\n-- list --\n";    demo_list();
    std::cout << "\n-- map --\n";     demo_map();
    std::cout << "\n-- umap --\n";    demo_unordered_map();
    std::cout << "\n-- sets --\n";    demo_sets();
    std::cout << "\n-- array --\n";   demo_array();
    std::cout << "\n-- adaptors --\n"; demo_adaptors();

    return 0;
}
