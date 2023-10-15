#include <iostream>
#include <vector>
#include <algorithm>  // for std::shuffle
#include <random>     // for std::mt19937 and std::random_device https://www.reddit.com/r/cpp/comments/iufxze/im_pretty_sure_theres_a_massive_widespread/ reference
#include "AVLTree.h"

int main() {
    // Create 3 sequences of odd numbers from 1 to 100.
    std::vector<int> ascending, descending, random;

    for (int i = 1; i <= 100; i += 2) {
        ascending.push_back(i);
        descending.insert(descending.begin(), i);
        random.push_back(i);
    }

    // Shuffle the random vector.
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(random.begin(), random.end(), g);

    // Create 3 AVL trees and insert the sequences.
    AVLTree<int> tree1, tree2, tree3;
    for (int i = 0; i < 50; ++i) {
        tree1.insert(ascending[i]);
        tree2.insert(descending[i]);
        tree3.insert(random[i]);
    }

    // Print heights of the AVL trees.
    std::cout << "Height of Tree1: " << tree1.height() << std::endl;
    std::cout << "Height of Tree2: " << tree2.height() << std::endl;
    std::cout << "Height of Tree3: " << tree3.height() << std::endl;

    // Validate the AVL trees.
    std::cout << "Validation of Tree1: " << (tree1.validate() ? "Balanced" : "Not Balanced") << std::endl;
    std::cout << "Validation of Tree2: " << (tree2.validate() ? "Balanced" : "Not Balanced") << std::endl;
    std::cout << "Validation of Tree3: " << (tree3.validate() ? "Balanced" : "Not Balanced") << std::endl;

    // Check if all odd numbers are present and even numbers are absent in the trees.
    for (int i = 1; i <= 100; ++i) {
        bool contains = (i % 2 != 0);
        if (tree1.contains(i) != contains || tree2.contains(i) != contains || tree3.contains(i) != contains) {
            std::cout << "My AVL tree implementation is wrong" << std::endl;
            return 1;  // Exit with an error code.
        }
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}



