/*
 * ============================================================
 * Module 07 — STL Algorithms (C++17)
 * ============================================================
 *
 * The <algorithm> and <numeric> headers provide generic,
 * iterator-based algorithms that work on any range satisfying
 * the required iterator category. They are the foundation of
 * the C++20 Ranges library covered in Module 17.
 *
 * Key concepts:
 *
 * 1. Sorting
 *    - std::sort         — O(n log n), not stable (introsort)
 *    - std::stable_sort  — O(n log n), preserves relative order of equals
 *    - std::partial_sort — cheapest way to find the k smallest elements
 *    - Custom comparators: lambda or function object
 *
 * 2. Searching
 *    - std::find, std::find_if, std::find_if_not
 *    - std::binary_search, std::lower_bound, std::upper_bound (sorted range)
 *    - std::count, std::count_if
 *    - All return iterators; check against end() for "not found"
 *
 * 3. Transformation
 *    - std::transform — maps a range through a function into an output range
 *    - std::for_each  — applies a function to each element (side effects OK)
 *    - std::copy, std::copy_if — filter while copying
 *    - std::fill, std::generate — populate a range
 *
 * 4. Partitioning & reordering
 *    - std::partition     — elements satisfying predicate come first
 *    - std::stable_partition — same, but preserves relative order
 *    - std::rotate        — cyclic left rotation
 *    - std::reverse       — reverse a range in-place
 *    - std::unique        — remove consecutive duplicates (pair with sort)
 *
 * 5. Numeric algorithms (<numeric>)
 *    - std::accumulate    — fold/reduce with an initial value and binary op
 *    - std::inner_product — dot product or custom 2-range fold
 *    - std::iota          — fill with incrementing sequence
 *    - std::partial_sum   — prefix sums
 *    - std::reduce (C++17) — like accumulate but execution-policy aware
 *    - std::transform_reduce (C++17) — parallel map-reduce
 *
 * 6. Iterator adaptors
 *    - std::back_inserter — calls push_back on each output write
 *    - std::inserter      — calls insert at a given position
 *    - std::ostream_iterator — writes to a stream
 *
 * Build & run:
 *   make run MODULE=07_stl_algorithms
 * ============================================================
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

// ── 1. Sorting ────────────────────────────────────────────────────────────────
void demo_sort() {
    // TODO: Create vector<int> v = {5,3,8,1,9,2,7,4,6}.
    // TODO: Sort a copy with std::sort (ascending), print it.
    // TODO: Sort another copy with a custom comparator (descending), print it.

    // TODO: Create vector<pair<string,int>> with name-score pairs.
    //       Use stable_sort to sort by score ascending. Print before and after
    //       to show that equal scores preserve the original relative order.

    // TODO: Use partial_sort to find the 3 smallest elements.
}

// ── 2. Searching ─────────────────────────────────────────────────────────────
void demo_search() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // TODO: Use find() to locate value 7. Print the result.
    // TODO: Use find_if() to locate the first element > 5. Print it.
    // TODO: Use count_if() to count even numbers.
    // TODO: Use binary_search() on a sorted range; then lower_bound/upper_bound
    //       to find the insertion position for value 5.
}

// ── 3. Transformation ────────────────────────────────────────────────────────
void demo_transform() {
    std::vector<int> src = {1, 2, 3, 4, 5};

    // TODO: Use transform to produce a vector of squared values into a new vector.
    //       Use back_inserter as the output iterator.

    // TODO: Use copy_if to extract only odd numbers into another vector.

    // TODO: Use for_each to print each element with a prefix label.

    // TODO: Use generate to fill a vector<int>(5) with values 1,4,9,16,25
    //       using a stateful lambda counter.
}

// ── 4. Partitioning & reordering ─────────────────────────────────────────────
void demo_partition() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // TODO: Use partition to put even numbers first. Print the partition point.
    //       Print the vector and note that relative order within each partition
    //       may not be preserved.

    // TODO: On a fresh copy, use stable_partition. Compare with partition output.

    // TODO: Sort a vector, then use unique + erase to remove duplicates.
    //       Input: {3,1,4,1,5,9,2,6,5,3,5}

    // TODO: Use rotate to move the first 3 elements to the end. Print before/after.
}

// ── 5. Numeric algorithms ────────────────────────────────────────────────────
void demo_numeric() {
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 1);  // fill 1..10

    // TODO: Use accumulate to compute the sum. Expected: 55.
    // TODO: Use accumulate with a custom binary op (lambda) to compute product.

    // TODO: Compute inner_product of v with itself (sum of squares).

    // TODO: Compute partial_sum of v and print the prefix-sum vector.

    // TODO: Use transform_reduce (C++17) to compute sum of squares in one call.
    //       (Hint: transform op = square, reduce op = plus)
}

int main() {
    std::cout << "=== 07: STL Algorithms ===\n\n";

    std::cout << "-- Sorting --\n";   demo_sort();
    std::cout << "\n-- Searching --\n"; demo_search();
    std::cout << "\n-- Transform --\n"; demo_transform();
    std::cout << "\n-- Partition --\n"; demo_partition();
    std::cout << "\n-- Numeric --\n";  demo_numeric();

    return 0;
}
