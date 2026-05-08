#include <iostream>
#include <memory>
#include <vector>

#include "computation.hpp"
#include "tree.hpp"

int main() {
    std::cout << "SSS* simulator\n";

    Case c1 { Case1 {} };
    Case c2 { Case2 {} };
    std::cout << "Two cases:" << c1.name() << ' ' << c2.name() << '\n';

    std::shared_ptr<TreeNode<3>> tree = std::make_shared<TreeNode<3>>(TreeNode<3>(2, true));
    std::vector<int> merits { 9, 6, 3, 8, 5, 2, 7, 4, 1 };
    auto it = merits.begin();
    tree->fill_with_values(it, merits.begin(), merits.end());

    auto n1 = tree->first().value();
    auto n2 = n1->next().value();
    auto n3 = n2->next().value();

    std::cout << "n11:" << n1->first().value()->getMerit() << '\n';
    std::cout << "n12:" << n1->first().value()->next().value()->getMerit() << '\n';
    std::cout << "n13:" << n1->first().value()->next().value()->next().value()->getMerit() << '\n';

    std::cout << "n21:" << n2->first().value()->getMerit() << '\n';
    std::cout << "n22:" << n2->first().value()->next().value()->getMerit() << '\n';
    std::cout << "n23:" << n2->first().value()->next().value()->next().value()->getMerit() << '\n';

    std::cout << "n31:" << n3->first().value()->getMerit() << '\n';
    std::cout << "n32:" << n3->first().value()->next().value()->getMerit() << '\n';
    std::cout << "n33:" << n3->first().value()->next().value()->next().value()->getMerit() << '\n';

    return 0;
}
