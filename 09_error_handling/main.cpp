/*
 * ============================================================
 * Module 09 — Error Handling (C++17/23)
 * ============================================================
 *
 * C++ offers several error-handling strategies. Choosing the right
 * one depends on whether the error is recoverable, how frequent it
 * is on the hot path, and whether you're in a noexcept context
 * (e.g., embedded, real-time, or low-latency code).
 *
 * Key concepts:
 *
 * 1. Exceptions
 *    - throw / try / catch mechanism
 *    - Derive custom exceptions from std::exception; override what()
 *    - Exception hierarchy: std::runtime_error, std::logic_error, etc.
 *    - Stack unwinding: destructors run on the way out (RAII safety)
 *    - catch (...) to catch anything; prefer specific types first
 *    - Re-throwing: `throw;` (not `throw e;`) preserves the original exception
 *
 * 2. noexcept
 *    - Declares a function will never throw
 *    - Enables optimisations: move constructors are faster when noexcept
 *    - Violating noexcept calls std::terminate()
 *    - noexcept(expr): conditionally noexcept based on an expression
 *
 * 3. Error codes — std::error_code / std::error_condition
 *    - Portable, allocation-free error reporting
 *    - Used extensively in networking (Asio, std::net)
 *    - Prefer when exceptions are disabled or overhead matters
 *
 * 4. std::optional<T> (C++17)
 *    - Represents a value that may or may not be present
 *    - No heap allocation; fits in sizeof(T)+1 (roughly)
 *    - Use for nullable return values instead of raw pointers or sentinel values
 *    - Access: *opt, opt.value(), opt.value_or(default)
 *    - Check: if (opt), opt.has_value()
 *
 * 5. std::expected<T, E> (C++23)
 *    - Either a value T or an error E — like Rust's Result<T,E>
 *    - Access value: *exp or exp.value()
 *    - Access error: exp.error()
 *    - Check: exp.has_value(), if (exp)
 *    - Preferred over exceptions for functions that commonly fail
 *
 * Build & run:
 *   make run MODULE=09_error_handling
 * ============================================================
 */

#include <expected>  // C++23
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <system_error>

// ── 1. Custom exception ──────────────────────────────────────────────────────
// TODO: Define class SensorError : public std::runtime_error
//       with a constructor that takes a string message.

// TODO: Define class CalibrationError : public SensorError
//       that adds an int sensor_id member and includes it in what().

// ── 2. Exception throw/catch ──────────────────────────────────────────────────
// TODO: Write `double read_sensor(int id)`:
//   - If id < 0: throw SensorError("negative id")
//   - If id == 0: throw CalibrationError("not calibrated", id)
//   - Otherwise: return id * 1.5

void demo_exceptions() {
    // TODO: Call read_sensor with id=-1, 0, and 3.
    //       Wrap each in try/catch:
    //         catch (const CalibrationError&) first (most specific)
    //         catch (const SensorError&) second
    //         catch (const std::exception&) last
    // TODO: In the catch block, print e.what().
    // TODO: Demonstrate re-throw: catch an exception, log it, then `throw;`.
}

// ── 3. noexcept ──────────────────────────────────────────────────────────────
// TODO: Write `int safe_divide(int a, int b) noexcept`:
//       Return a/b if b != 0, else return 0.
//       Note: with noexcept, you cannot propagate an exception — handle inline.

// TODO: Write `void might_throw()` that throws std::runtime_error.
//       Write `void safe_wrapper() noexcept` that calls might_throw() inside
//       a try/catch and prints the error, swallowing it.

// ── 4. std::optional ─────────────────────────────────────────────────────────
// TODO: Write `std::optional<double> parse_double(const std::string& s)`:
//   - Try std::stod; on failure (std::invalid_argument, std::out_of_range)
//     return std::nullopt.
//   - On success return the parsed value.

void demo_optional() {
    // TODO: Call parse_double with "3.14", "abc", and "".
    //       For each, check has_value() and print the result or "parse failed".
    // TODO: Use value_or(-1.0) to provide a default.
    // TODO: Chain: if (auto v = parse_double("42.0"); v) { use *v }
}

// ── 5. std::expected (C++23) ─────────────────────────────────────────────────
// TODO: Define an enum class ParseError { empty_input, invalid_number, overflow }.

// TODO: Write `std::expected<double, ParseError> safe_parse(const std::string& s)`:
//   - Return std::unexpected(ParseError::empty_input) if s is empty
//   - Return std::unexpected(ParseError::invalid_number) on bad format
//   - Return the parsed double on success

void demo_expected() {
    // TODO: Call safe_parse with "2.71", "", "not_a_number".
    //       Use if (result) to branch, result.value() and result.error().
    // TODO: Use .value_or(0.0) as a fallback.
    // TODO: Compare the readability of this vs the optional version — comment.
}

int main() {
    std::cout << "=== 09: Error Handling ===\n\n";

    std::cout << "-- Exceptions --\n";   demo_exceptions();
    std::cout << "\n-- noexcept --\n";
    // TODO: Print safe_divide(10, 3) and safe_divide(10, 0).
    // TODO: Call safe_wrapper().

    std::cout << "\n-- std::optional --\n"; demo_optional();
    std::cout << "\n-- std::expected --\n"; demo_expected();

    return 0;
}
