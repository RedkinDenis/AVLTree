#include <iostream>
#include "include/tree.hpp"

// using namespace Trees;

int main () {

    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    std::cout << "Inorder: ";
    tree.inOrder();

    return 0;
}