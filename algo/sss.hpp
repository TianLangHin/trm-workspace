#ifndef SSS_HPP
#define SSS_HPP

#include <algorithm>
#include <compare>
#include <limits>
#include <list>
#include <memory>
#include <stdexcept>
#include <variant>
#include <vector>

#include "computation.hpp"
#include "tree.hpp"

struct Live : std::monostate {};
struct Solved : std::monostate {};

template <int Width>
struct State {
    std::shared_ptr<TreeNode<Width>> v;
    std::variant<Live, Solved> s;
    int h;

    // C++ Development Lesson 8: The spaceship operator here is defined
    // to use the operations purely from the merit value of a SSS* state,
    // defining all six comparison functions at once.
    std::strong_ordering operator<=>(const State& other) {
        return h <=> other.h;
    }
};

template <int Width>
int sss(std::shared_ptr<TreeNode<Width>> root, std::vector<Case>& computation_path, int& leaf_count) {
    // C++ Development Lesson 7: using list-braces for initialisation.
    // Modern C++ Lesson 2: using `std::move` for non-copying transfer of shared pointer.
    std::list<State<Width>> open { { std::move(root), Live {}, std::numeric_limits<int>::max() } };

    while (!open.empty()) {
        // Modern C++ Lesson 6: using structured bindings to unpack a struct easily.
        auto [v, s, h] = open.front();
        open.pop_front();

        if (v->parent().has_value() && std::holds_alternative<Solved>(s)) {
            if (!v->getPlayer()) {
                std::shared_ptr<TreeNode<Width>> parent_node = v->parent().value();
                // C++ Development Lesson 3: usage of a lambda as an algorithm predicate.
                // Modern C++ Lesson 5: Using the `[&]` syntax for variable capture by reference.
                open.remove_if([&](auto state) {
                    std::shared_ptr<TreeNode<Width>> node(state.v);
                    while (node != parent_node) {
                        auto parent = node->parent();
                        if (parent.has_value()) {
                            node = parent.value();
                        } else {
                            break;
                        }
                    }
                    return node == parent_node;
                });
                open.push_front({ parent_node, Solved {}, h });
                computation_path.push_back({Case1 {}});
            } else if (v->getPlayer()) {
                std::optional<std::shared_ptr<TreeNode<Width>>> next_node = v->next();
                if (next_node.has_value()) {
                    open.push_front({ std::move(next_node.value()), Live {}, h });
                    computation_path.push_back({Case2 {}});
                } else {
                    open.push_front({ v->parent().value(), Solved {}, h });
                    computation_path.push_back({Case3 {}});
                }
            }
        } else if (std::holds_alternative<Live>(s)) {
            std::optional<std::shared_ptr<TreeNode<Width>>> first_child = v->first();
            if (!first_child.has_value()) {
                State<Width> new_state { v, Solved {}, std::min(v->getMerit(), h) };
                // Modern C++ Lesson 3: using `auto` for improved initialisation since the result is a long iterator type.
                // Modern C++ Lesson 5: using `[&new_state]` in the lambda for capturing only one variable.
                auto insertion_location = std::find_if(open.cbegin(), open.cend(), [&new_state](auto element) {
                    return element.h < new_state.h;
                });
                open.insert(insertion_location, new_state);
                ++leaf_count;
                computation_path.push_back({Case4 {}});
            } else {
                if (!v->getPlayer()) {
                    open.push_front({ first_child.value(), Live {}, h });
                    computation_path.push_back({Case5 {}});
                } else {
                    for (auto child : v->getChildren().value()) {
                        open.push_front({ std::move(child), Live {}, h });
                    }
                    computation_path.push_back({Case6 {}});
                }
            }
        } else {
            return h;
        }
    }
    throw std::runtime_error("This is unreachable, since the state space operator must keep OPEN non-empty.");
}

#endif
