#ifndef ALPHA_BETA_HPP
#define ALPHA_BETA_HPP

#include <algorithm>
#include <memory>

#include "tree.hpp"

template <int Width>
int alpha_beta(std::shared_ptr<TreeNode<Width>> node, int alpha, int beta, int& leaf_count) {
    if (!node->first().has_value()) {
        ++leaf_count;
        int value = node->getMerit();
        return node->getPlayer() ? value : -value;
    }
    int best_eval = alpha;
    for (auto child : node->getChildren().value()) {
        int eval = -alpha_beta(child, -beta, -best_eval, leaf_count);
        best_eval = std::max(best_eval, eval);
        if (best_eval >= beta) {
            return beta;
        }
    }
    return best_eval;
}

#endif
