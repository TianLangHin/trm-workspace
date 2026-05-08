#ifndef TREE_HPP
#define TREE_HPP

#include <array>
#include <iterator>
#include <memory>
#include <optional>

template <int Width>
class TreeNode : public std::enable_shared_from_this<TreeNode<Width>> {
private:
    int merit;
    bool player;

    // Modern C++ Lesson 1: Improved type declarations (`using` rather than `typedef`).
    using SharedPtr = std::shared_ptr<TreeNode<Width>>;
    using WeakPtr = std::weak_ptr<TreeNode<Width>>;

    // C++ Development Lesson 5: Using an `optional`, since the array must be of size `Width` or be empty.
    std::optional<std::array<SharedPtr, Width>> children;
    WeakPtr parentPtr;
    WeakPtr nextPtr;

public:
    // Modern C++ Lesson 3: Uniform initialisation syntax used in the constructor.
    TreeNode(int depth, bool player): merit {0}, player {player}, parentPtr {}, nextPtr {} {
        if (depth <= 0) {
            this->children = {};
        } else {
            this->children = std::array<SharedPtr, Width> {};
            for (auto& child : this->children.value()) {
                child = std::make_shared<TreeNode<Width>>(TreeNode(depth - 1, !player));
            }
            for (int i = 0; i < Width - 1; ++i) {
                this->children.value()[i]->nextPtr = WeakPtr(this->children.value()[i+1]);
            }
        }
    }

    // Modern C++ Lesson 1: Improved type declaration within a template specifying a forward iterator.
    template <std::forward_iterator It>
    void fill_with_values(It& curr, It begin, It end) {
        if (!children.has_value()) {
            if (curr == end) {
                this->merit = 0;
            } else {
                this->merit = *(curr++);
            }
            return;
        }
        for (auto& child : children.value()) {
            // Modern C++ Lesson 3: using `enable_shared_from_this`.
            // Allows a shared pointer to be constructed pointing to this object.
            child->parentPtr = WeakPtr(this->shared_from_this());
            child->fill_with_values(curr, begin, end);
        }
    }

    std::optional<SharedPtr> parent() {
        // Modern C++ Lesson 4: Checking weak pointer object validity status.
        if (parentPtr.expired()) {
            // C++ Development Lesson 5: empty initialisation constructs `nullopt` for optional.
            return {};
        }
        // Modern C++ Lesson 4: Converting weak pointer to shared pointer.
        return parentPtr.lock();
    }

    std::optional<SharedPtr> first() {
        // C++ Development Lesson 5: Using `has_value` and `value()`
        // to check/retrieve possibly empty values from an optional.
        if (!children.has_value()) {
            return {};
        }
        return children.value()[0];
    }

    std::optional<SharedPtr> next() {
        if (nextPtr.expired()) {
            return {};
        }
        return nextPtr.lock();
    }

    std::optional<std::array<SharedPtr, Width>> getChildren() {
        return children;
    }

    int getMerit() {
        return merit;
    }

    bool getPlayer() {
        return player;
    }
};

#endif
