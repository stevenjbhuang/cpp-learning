/*
 * ============================================================
 * Module 17 — Ranges (C++20)
 * ============================================================
 *
 * The Ranges library unifies the iterator-based STL algorithms
 * with a composable, lazy pipeline syntax. Views transform
 * ranges without allocating intermediate containers.
 *
 * Key concepts:
 *
 * 1. Ranges vs iterators
 *    - A range is any type with begin() and end()
 *    - std::ranges::* algorithms take ranges directly (no begin/end pair)
 *    - Cleaner call sites: std::ranges::sort(v) vs std::sort(v.begin(),v.end())
 *    - Projections: sort by member without a comparator lambda
 *
 * 2. Views — lazy, non-owning transformations
 *    - std::views::filter(pred)   — only elements satisfying pred
 *    - std::views::transform(fn)  — map each element through fn
 *    - std::views::take(n)        — first n elements
 *    - std::views::drop(n)        — skip first n elements
 *    - std::views::reverse        — iterate in reverse
 *    - std::views::iota(n)        — infinite sequence 0,1,2,...
 *    - std::views::keys / values  — first/second of map pairs
 *    - std::views::enumerate (C++23) — (index, value) pairs
 *    - std::views::zip (C++23)    — zip two ranges together
 *
 * 3. Pipeline operator |
 *    - Chains views: vec | views::filter(even) | views::transform(square)
 *    - Each view is composed lazily — no intermediate allocations
 *    - Materialise with std::ranges::to<std::vector>() (C++23)
 *      or a manual copy_n / for loop
 *
 * 4. Range algorithms
 *    - std::ranges::sort, find, find_if, copy, transform, for_each
 *    - std::ranges::any_of, all_of, none_of
 *    - std::ranges::count, count_if, min_element, max_element
 *    - Projections: ranges::sort(v, {}, &Person::age) — sort by age
 *
 * 5. Range factories
 *    - std::views::iota(begin, end)  — [begin, end) sequence
 *    - std::views::repeat(val)       — infinite same-value range (C++23)
 *    - std::views::single(val)       — single element range
 *    - std::views::empty<T>          — empty range of type T
 *
 * 6. Sentinels & counted ranges
 *    - std::views::counted(it, n)    — range of n elements from iterator
 *    - A sentinel is an end condition that may differ in type from the iterator
 *
 * Build & run:
 *   make run MODULE=17_ranges_cpp20
 * ============================================================
 */

#include <algorithm>
#include <iostream>
#include <map>
#include <ranges>
#include <string>
#include <vector>

// ── 1. ranges:: algorithms vs classic algorithms ──────────────────────────────
void demo_ranges_algorithms() {
    std::vector<int> v = {5, 3, 8, 1, 9, 2, 7, 4, 6};

    // TODO: Sort v using std::ranges::sort. Print result.
    // TODO: Find value 7 using std::ranges::find. Check result != v.end().
    // TODO: Use ranges::count_if to count even numbers.

    struct Person { std::string name; int age; };
    std::vector<Person> people = {{"Alice",30}, {"Bob",25}, {"Carol",35}};
    // TODO: Sort people by age using ranges::sort with a projection:
    //       ranges::sort(people, {}, &Person::age);
    //       Print names in sorted order.
}

// ── 2. Views & pipelines ──────────────────────────────────────────────────────
void demo_views() {
    std::vector<int> nums(20);
    std::iota(nums.begin(), nums.end(), 1);  // 1..20

    // TODO: Build a pipeline: even numbers, squared, first 5.
    //         nums | views::filter(even) | views::transform(sq) | views::take(5)
    //       Print each element (use for loop over the view).

    // TODO: Use views::iota(1, 11) | views::reverse to print 10 down to 1.

    // TODO: Use views::keys on a std::map<string,int> to print all keys.
}

// ── 3. Materialising a view ───────────────────────────────────────────────────
void demo_materialise() {
    // TODO: Build a view pipeline (e.g., filter + transform over iota(1,21)).
    //       Materialise it into a std::vector<int> using:
    //         std::vector<int> result(view.begin(), view.end());
    //       or with ranges::copy into a back_inserter.
    // TODO: Print the materialised vector's size and contents.
}

// ── 4. Custom range: generate a Fibonacci sequence view ──────────────────────
// TODO: Implement a simple generator as a view using views::iota + transform,
//       or as a hand-rolled input range:
//
//   struct FibRange {
//     struct iterator {
//       int a = 0, b = 1;
//       int operator*() const { return a; }
//       iterator& operator++() { auto tmp = a+b; a = b; b = tmp; return *this; }
//       bool operator==(std::default_sentinel_t) const { return false; }  // infinite
//     };
//     iterator begin() const { return {}; }
//     std::default_sentinel_t end() const { return {}; }
//   };
//
// TODO: Print the first 10 Fibonacci numbers using:
//   FibRange{} | views::take(10)

// ── 5. views::zip and views::enumerate (C++23) ───────────────────────────────
void demo_zip_enumerate() {
    std::vector<std::string> names = {"lidar", "imu", "camera"};
    std::vector<double> readings  = {12.5, 9.81, 0.0};

    // TODO: Use views::zip(names, readings) to iterate both together.
    //       Print "sensor: <name> = <reading>" for each pair.

    // TODO: Use views::enumerate(names) to print "0: lidar", "1: imu", etc.
}

int main() {
    std::cout << "=== 17: Ranges (C++20) ===\n\n";

    std::cout << "-- Range algorithms --\n";   demo_ranges_algorithms();
    std::cout << "\n-- Views & pipelines --\n"; demo_views();
    std::cout << "\n-- Materialise --\n";       demo_materialise();
    std::cout << "\n-- Custom range (Fib) --\n";
    // TODO: Print Fibonacci view output here.
    std::cout << "\n-- zip / enumerate --\n";   demo_zip_enumerate();

    return 0;
}
