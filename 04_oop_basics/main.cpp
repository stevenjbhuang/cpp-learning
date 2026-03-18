/*
 * ============================================================
 * Module 04 — OOP Basics (C++17)
 * ============================================================
 *
 * Object-oriented programming in C++ goes beyond Java/Python OOP.
 * Value semantics, deterministic destruction, and manual resource
 * management are first-class concerns. This module focuses on
 * writing correct, efficient classes.
 *
 * Key concepts:
 *
 * 1. Class anatomy
 *    - Member variables, member functions, access specifiers
 *    - Constructors (default, parameterised, delegating)
 *    - Destructor: runs deterministically when the object leaves scope
 *    - `explicit` constructors: prevent accidental implicit conversions
 *
 * 2. Rule of Five (or Zero)
 *    - If you manually manage a resource, define all five:
 *        destructor, copy constructor, copy assignment,
 *        move constructor, move assignment
 *    - Rule of Zero: prefer owning containers/smart pointers so you
 *        need none of these
 *    - noexcept on move operations enables STL optimisations
 *
 * 3. Inheritance & virtual dispatch
 *    - `virtual` method: resolved at runtime via vtable
 *    - Pure virtual (= 0): makes the class abstract
 *    - `override` keyword: compiler checks you really override a base method
 *    - `final`: prevents further derivation or override
 *    - Always declare the base-class destructor virtual
 *
 * 4. Abstract base classes
 *    - Cannot be instantiated directly
 *    - Define an interface that derived classes must implement
 *    - Useful for polymorphism via base-class pointers/references
 *
 * 5. Static members
 *    - Shared across all instances of the class
 *    - `inline static` (C++17): defined inside the class header
 *    - Static member functions: callable without an instance
 *
 * 6. Polymorphism with smart pointers
 *    - Store derived objects via std::unique_ptr<Base>
 *    - Enables heterogeneous containers
 *    - The virtual destructor ensures correct cleanup
 *
 * Build & run:
 *   make run MODULE=04_oop_basics
 * ============================================================
 */

#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

// ── 1. Basic class with Rule of Five ─────────────────────────────────────────
// TODO: Implement class `Buffer` that owns a heap-allocated int array.
//
//   Public interface:
//     explicit Buffer(std::size_t size)   — allocates with new int[size]{}
//     ~Buffer()                           — deallocates with delete[]
//     Buffer(const Buffer&)               — deep copy
//     Buffer& operator=(const Buffer&)    — copy-assign (handle self-assignment)
//     Buffer(Buffer&&) noexcept           — steal the pointer, null out source
//     Buffer& operator=(Buffer&&) noexcept
//     std::size_t size() const
//
//   Each special member should print a message so you can observe lifetimes.
//
// class Buffer { ... };

// ── 2. Inheritance & virtual dispatch ────────────────────────────────────────
// TODO: Implement an abstract base class `Sensor`:
//   - Constructor takes a std::string_view name, stores it as std::string
//   - virtual destructor = default
//   - Pure virtual: `virtual double read() const = 0`
//   - Non-pure virtual with default impl: `virtual void calibrate()`
//     prints "[<name>] default calibration"
//   - Accessor: `std::string_view name() const`
//
// TODO: Derive `Lidar` from Sensor (mark it `final`):
//   - Constructor takes name and double range_m
//   - override read() → returns range_m * 0.95
//   - override calibrate() → prints "[<name>] LIDAR-specific calibration"
//
// TODO: Derive `IMU` from Sensor:
//   - Constructor takes name
//   - override read() → returns 9.81 (simulated accel magnitude)
//   - Does NOT override calibrate() — uses the base default

// ── 3. Static members ────────────────────────────────────────────────────────
// TODO: Implement class `SensorRegistry`:
//   - inline static int count_ = 0;   (C++17)
//   - static void register_sensor()   — increments count_
//   - static int count()              — returns count_

// ── 4. Polymorphic usage ──────────────────────────────────────────────────────
// TODO: Write `void poll_all(const std::vector<std::unique_ptr<Sensor>>& sensors)`
//       that iterates and prints each sensor's name and read() value.

int main() {
    std::cout << "=== 04: OOP Basics ===\n\n";

    // Rule of Five — observe constructor/destructor messages
    std::cout << "-- Rule of Five --\n";
    {
        // TODO: Create Buffer b1(4), copy it to b2, move it to b3.
        //       Verify the expected print messages appear.
    }  // all three destroyed here

    // Abstract base + polymorphism
    std::cout << "\n-- Polymorphism --\n";
    {
        std::vector<std::unique_ptr<Sensor>> sensors;
        // TODO: Add a Lidar("front_lidar", 10.0), Lidar("rear_lidar", 5.0),
        //       and IMU("imu0") to the vector using make_unique.
        // TODO: Call poll_all(sensors).
        // TODO: Call calibrate() on each sensor via the base pointer.
    }

    // Static members
    std::cout << "\n-- Static members --\n";
    // TODO: Call SensorRegistry::register_sensor() twice.
    //       Print SensorRegistry::count().

    return 0;
}
