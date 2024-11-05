#include <iostream>
#include "include/tree.hpp"
#include <gtest/gtest.h>

// #define FULL_TESTING
// #define UNIT_TESTING

int main () {

#if defined(UNIT_TESTING) || defined(FULL_TESTING)

    testing::InitGoogleTest();
    auto r = RUN_ALL_TESTS();
#else    
    AVLTree<int> tree;

    tree.run();
    std::cout << std::endl;

    return 0;
#endif
}

#ifdef FULL_TESTING

#define GTEST(name, dat, ans)           \
TEST(counting, name) {                  \
                                        \
    AVLTree<int> tree;                  \
                                        \
    std::stringstream inp(dat);         \
    std::stringstream res;              \
    tree.run(inp, res);                 \
                                        \
    std::string answer(ans);            \
    ASSERT_TRUE(answer == res.str());   \
}

GTEST(test1, "k 10 k 20 q 8 31 q 6 9 k 30 k 40 q 15 40", "2 0 3 ")
GTEST(test2, "k 1 k 2 k 3 k 4 k 5 q 1 5", "5 ")
GTEST(test3, "k 1 k 2 k 3 q 1 3 k 4 k 5 q 1 3", "3 3 ")
#undef GTEST

#endif

#ifdef UNIT_TESTING

TEST(filling, test) {

    AVLTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);

    std::stringstream ans;
    tree.inOrder(ans);

    ASSERT_TRUE("1 2 3 4 5 6 " == ans.str());
}

#endif