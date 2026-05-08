#include <iostream>
#include <memory>
#include <vector>

#include "alpha_beta.hpp"
#include "computation.hpp"
#include "heuristics.hpp"
#include "sss.hpp"
#include "tree.hpp"

#ifndef TREE_WIDTH
#define TREE_WIDTH 2
#endif

int main() {
    constexpr int Width = TREE_WIDTH;
    static_assert(Width >= 2, "Tree width must be 2 or more.");

    int depth;
    std::cout << "Tree width is " << Width << ". Enter depth of tree: ";
    std::cin >> depth;
    std::cout << '\n';

    int limit = std::numeric_limits<int>::max();

    auto [bestValues, worstValues] = heuristics(Width, depth);

    std::vector<Case> bestPath {};
    auto bestNode = std::make_shared<TreeNode<Width>>(TreeNode<Width>(depth, true));
    auto bestIt = bestValues.begin();
    bestNode->fill_with_values(bestIt, bestValues.begin(), bestValues.end());
    int sssLeafBest = 0, abLeafBest = 0;
    int sssBest = sss(bestNode, bestPath, sssLeafBest);
    int abBest = alpha_beta(bestNode, -limit, limit, abLeafBest);

    std::vector<Case> worstPath {};
    auto worstNode = std::make_shared<TreeNode<Width>>(TreeNode<Width>(depth, true));
    auto worstIt = worstValues.begin();
    worstNode->fill_with_values(worstIt, worstValues.begin(), worstValues.end());
    int sssLeafWorst = 0, abLeafWorst = 0;
    int sssWorst = sss(worstNode, worstPath, sssLeafWorst);
    int abWorst = alpha_beta(worstNode, -limit, limit, abLeafWorst);

    std::cout << "Best-Case SSS* Computation Path:\n";
    for (auto c : bestPath) {
        std::cout << c.name() << ' ';
    }
    std::cout << '\n';

    std::cout << "Worst-Case SSS* Computation Path:\n";
    for (auto c : worstPath) {
        std::cout << c.name() << ' ';
    }
    std::cout << '\n';

    std::cout << "Best-Case:\n";
    std::cout << "SSS* Result: " << sssBest << ", Alpha-Beta Result: " << abBest << '\n';
    std::cout << "SSS* Leaf Count: " << sssLeafBest << ", Alpha-Beta Leaf Count: " << abLeafBest << '\n';
    std::cout << "Worst-Case:\n";
    std::cout << "SSS* Result: " << sssWorst << ", Alpha-Beta Result: " << abWorst << '\n';
    std::cout << "SSS* Leaf Count: " << sssLeafWorst << ", Alpha-Beta Leaf Count: " << abLeafWorst << '\n';
}
