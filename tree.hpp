#ifndef TREE_HPP
#define TREE_HPP

#include <array>
#include <memory>
#include <optional>

template <int Width>
class TreeNode {
private:
    int merit;
    bool player;

    std::optional<std::array<std::shared_ptr<TreeNode<Width>>, Width>> children;
    std::weak_ptr<TreeNode<Width>> parentPtr;
    std::weak_ptr<TreeNode<Width>> nextPtr;
}

#endif
