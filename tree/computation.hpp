#ifndef COMPUATION_HPP
#define COMPUATION_HPP

#include <variant>

struct Case1 : std::monostate {};
struct Case2 : std::monostate {};
struct Case3 : std::monostate {};
struct Case4 : std::monostate {};
struct Case5 : std::monostate {};
struct Case6 : std::monostate {};

// C++ Development Lesson 5: using the `std::variant` class
// to store one of six finite possibilities in value.
class Case : public std::variant<Case1, Case2, Case3, Case4, Case5, Case6> {
public:
    char name() {
        // C++ Development Lesson 5: using the `visit` method to
        // check the value of a variant and branch according to it.
        return std::visit([](auto&& arg) {
            // Modern C++ Lesson 1: use of the `decltype` keyword to use
            // the existing anonymous type of another variable in declaring another.
            using T = std::decay_t<decltype(arg)>;

            // Modern C++ Lesson 1: use of the `constexpr` keyword to tell the compiler
            // to evaluate or precompute these branches are compile time.
            if constexpr (std::is_same_v<T, Case1>) {
                return '1';
            } else if constexpr (std::is_same_v<T, Case2>) {
                return '2';
            } else if constexpr (std::is_same_v<T, Case3>) {
                return '3';
            } else if constexpr (std::is_same_v<T, Case4>) {
                return '4';
            } else if constexpr (std::is_same_v<T, Case5>) {
                return '5';
            } else if constexpr (std::is_same_v<T, Case6>) {
                return '6';
            } else {
                // Modern C++ Lesson 1 (miscellany): using a compile-time assertion
                // to cover for unexpected edge cases.
                static_assert(false, "Impossible, since there are only 6 cases.");
            }
        }, *this);
    }
};

#endif
