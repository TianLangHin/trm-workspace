#ifndef HEURISTICS_HPP
#define HEURISTICS_HPP

#include <algorithm>
#include <functional>
#include <numeric>
#include <optional>
#include <ranges>
#include <utility>
#include <vector>

std::pair<std::vector<int>, std::vector<int>> heuristics(int width, int depth) {
    auto half_ceil = [](int x) { return (x + 1) / 2; };
    auto half_floor = [](int x) { return x / 2; };

    // Modern C++ Lesson 5: A lambda referencing itself using `this auto&` since it is fundamentally an object,
    // and also with specified return type using arrow annotation.
    auto pow = [](this auto& self, int a, int b) -> int {
        if (b == 0) {
            return 1;
        } else if (b == 1) {
            return a;
        }
        int tmp = self(a, b / 2);
        return b % 2 == 0 ? tmp * tmp : a * tmp * tmp;
    };

    // Modern C++ Lesson 5: using the `[=]` syntax for variable capture by copy.
    auto equivalent_position = [=](int index) {
        std::vector<int> position(depth);
        for (std::size_t i = 0; i < (std::size_t)depth; ++i) {
            position[depth - i - 1] = (index % width) + 1;
            index /= width;
        }
        return position;
    };

    auto alternate_p_structure = [=](std::vector<int>& q) -> std::vector<int> {
        auto first_not_one_it = std::find_if(q.cbegin(), q.cend(), [&q](auto e) { return e != 1; });
        if (first_not_one_it == q.cend()) {
            return {};
        }
        int j = first_not_one_it - q.cbegin();
        std::vector<int> structure {};
        for (int i = 0; i < j + 1; ++i) {
            structure.push_back(width);
        }
        for (int i = (int)j + 1; i < half_ceil(depth); ++i) {
            structure.push_back(1);
        }
        return structure;
    };

    std::vector<int> best_values {};
    std::vector<int> worst_values {};

    std::size_t total = pow(width, depth);

    for (std::size_t index = 0; index < total; ++index) {
        std::vector<int> position = equivalent_position((int)index);

        std::vector<int> p {};
        std::vector<int> q {};
        for (std::size_t i = 0; i < (std::size_t)depth; ++i) {
            if (i % 2 == 0) {
                p.push_back(position[i]);
            } else {
                q.push_back(position[i]);
            }
        }

        auto p_range = std::views::iota(1, half_ceil(depth) + 1);
        int p_term = std::transform_reduce(
            p_range.cbegin(),
            p_range.cend(),
            0,
            std::plus<int> {},
            [=](int k) {
                return pow(width, half_ceil(depth) - k) * (p[k - 1] - 1);
            });

        auto q_range = std::views::iota(1, half_floor(depth) + 1);
        int q_term = std::transform_reduce(
            q_range.cbegin(),
            q_range.cend(),
            0,
            std::plus<int> {},
            [=](int k) {
                return pow(width, half_floor(depth) - k) * (q[k - 1] - 1);
            });

        bool p_is_all_w = std::all_of(p.cbegin(), p.cend(), [=](auto pi) { return pi == width; });
        bool q_is_all_1 = std::all_of(q.cbegin(), q.cend(), [](auto qi) { return qi == 1; });

        int best_value = (p_is_all_w && q_is_all_1) || alternate_p_structure(q) == p
            ? pow(width, half_ceil(depth)) + 1
            : q_is_all_1 ? p_term + 1 : 0;

        best_values.push_back(best_value);
        worst_values.push_back(pow(width, depth) - p_term - pow(width, half_ceil(depth)) * q_term);
    }

    return { best_values, worst_values };
}

#endif
