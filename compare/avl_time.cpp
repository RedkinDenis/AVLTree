#include <iostream>
#include "ANSI_colors.hpp"
#include "tree.hpp"
#include "benchmark.hpp"

int main()
{
    using clock = std::chrono::high_resolution_clock;
    AVLTree<int> avl_tree;
    
    auto time_start = clock::now().time_since_epoch().count();
    char command;
    while(std::cin >> command) {
        int lower, upper, answer;
        switch (command) {
            case 'k':
                std::cin >> lower;
                avl_tree.insert(lower);
                break;

            case 'q':
                std::cin >> lower >> upper;
                if (lower < upper)
                    answer = avl_tree.countInRange(lower, upper);
                NO_OPT(answer);
                break;
        }
    }
    auto time_end = clock::now().time_since_epoch().count();
    long double time = (static_cast<long double>(time_end - time_start)) * NSEC_TO_SEC;
    std::cout << time << "\n";

    return 0;
}