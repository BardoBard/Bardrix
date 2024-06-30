//
// Created by Bardio on 22/06/2024.
//

#include <bardrix/algorithm.h>
#include <bardrix/point3.h>

bool int_predicate(int a, int b) {
    return a < b;
}

bool point_predicate(const bardrix::point3& a, const bardrix::point3& b) {
    return a.x < b.x;
}

/// \brief Test the building of a binary tree, with an array of points
TEST(binary_tree, build_array_points) {
    bardrix::binary_tree<bardrix::point3> tree(point_predicate);

    // 1, 10, 34, 64 (insert 2)->
    //       34
    //      /  \
    //     10  64
    //    /
    //   1
    //    \
    //     2 (inserted)
    std::vector<bardrix::point3> points2 = {
            { 1,  2,  3 },
            { 10, 0,  2 },
            { 34, 24, 55 },
            { 64, 37, 13 },
    };

    tree.build(points2.data(), points2.size());
    tree.insert({ 2, 3, 4 });

    EXPECT_EQ(tree.root->data.x, 34);
    EXPECT_EQ(tree.root->left->data.x, 10);
    EXPECT_EQ(tree.root->left->left->data.x, 1);
    EXPECT_EQ(tree.root->left->left->right->data.x, 2);
    EXPECT_EQ(tree.root->right->data.x, 64);
}

/// \brief Test the building of a binary tree, with begin and end iterators
TEST(binary_tree, build_iterators) {
    bardrix::binary_tree<int> tree(int_predicate);

    int values[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

    // 1, 2, 3, 4, 5, 6, 7, 8 ->
    //          5
    //        /   \
    //       3     7
    //      / \   / \
    //     2   4 6   8
    //    /
    //   1
    tree.build(values, values + sizeof values / sizeof values[0]);

    EXPECT_EQ(tree.root->data, 5);
    EXPECT_EQ(tree.root->left->data, 3);
    EXPECT_EQ(tree.root->right->data, 7);
    EXPECT_EQ(tree.root->left->left->data, 2);
    EXPECT_EQ(tree.root->left->left->left->data, 1);
    EXPECT_EQ(tree.root->left->right->data, 4);
    EXPECT_EQ(tree.root->right->left->data, 6);
    EXPECT_EQ(tree.root->right->right->data, 8);


    // 2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68 ->
    //            _____24_____
    //          /              \
    //        11               65
    //      /    \           /    \
    //     9      13       63     67
    //    / \     / \     / \    /  \
    //   2  10   12 14   62 64  66  68
    std::vector<int> values2 = { 2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68 };

    tree.build(values2.begin(), values2.end());

    EXPECT_EQ(tree.root->data, 24);
    EXPECT_EQ(tree.root->left->data, 11);
    EXPECT_EQ(tree.root->left->left->data, 9);
    EXPECT_EQ(tree.root->left->right->data, 13);
    EXPECT_EQ(tree.root->left->left->left->data, 2);
    EXPECT_EQ(tree.root->left->left->right->data, 10);
    EXPECT_EQ(tree.root->left->right->left->data, 12);
    EXPECT_EQ(tree.root->left->right->right->data, 14);
    EXPECT_EQ(tree.root->right->data, 65);
    EXPECT_EQ(tree.root->right->left->data, 63);
    EXPECT_EQ(tree.root->right->right->data, 67);
    EXPECT_EQ(tree.root->right->left->left->data, 62);
    EXPECT_EQ(tree.root->right->right->right->data, 68);
}

/// \brief Test the building of a binary tree, with an array of values
TEST(binary_tree, build_array) {
    bardrix::binary_tree<int> tree(int_predicate);

    int values[] = { 3, 5, 6, 7 };

    // 3, 5, 6, 7 ->
    //       6
    //      / \
    //     5   7
    //    /
    //   3
    tree.build(values, sizeof values / sizeof values[0]);

    EXPECT_EQ(tree.root->data, 6);
    EXPECT_EQ(tree.root->right->data, 7);
    EXPECT_EQ(tree.root->left->data, 5);
    EXPECT_EQ(tree.root->left->left->data, 3);

    // 1, 2, 3, 4, 5, 6, 7, 8 ->
    //          5
    //        /   \
    //       3     7
    //      / \   / \
    //     2   4 6   8
    //    /
    //   1
    std::vector<int> values2 = { 1, 2, 3, 4, 5, 6, 7, 8 };

    tree.build(values2.data(), values2.size());

    EXPECT_EQ(tree.root->data, 5);
    EXPECT_EQ(tree.root->right->data, 7);
    EXPECT_EQ(tree.root->left->data, 3);
    EXPECT_EQ(tree.root->right->right->data, 8);
    EXPECT_EQ(tree.root->right->left->data, 6);
    EXPECT_EQ(tree.root->left->right->data, 4);
    EXPECT_EQ(tree.root->left->left->data, 2);
    EXPECT_EQ(tree.root->left->left->left->data, 1);
}

/// \brief Test the building of a binary tree, with multiple values
TEST(binary_tree, build_multiple_values) {
    bardrix::binary_tree<int> tree(int_predicate);

    // 1, 3, 4, 5, 6, 7, 8 ->
    //       5
    //     /   \
    //    3     7
    //   / \   / \
    //  1   4 6   8
    tree.build(1, 3, 4, 5, 6, 7, 8);

    EXPECT_EQ(tree.root->data, 5);
    EXPECT_EQ(tree.root->left->data, 3);
    EXPECT_EQ(tree.root->right->data, 7);
    EXPECT_EQ(tree.root->left->left->data, 1);
    EXPECT_EQ(tree.root->left->right->data, 4);
    EXPECT_EQ(tree.root->right->left->data, 6);
    EXPECT_EQ(tree.root->right->right->data, 8);

    // 2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68 ->
    //            _____24_____
    //          /              \
    //        11               65
    //      /    \           /    \
    //     9      13       63     67
    //    / \     / \     / \    /  \
    //   2  10   12 14   62 64  66  68

    tree.build(2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68);

    EXPECT_EQ(tree.root->data, 24);
    EXPECT_EQ(tree.root->left->data, 11);
    EXPECT_EQ(tree.root->left->left->data, 9);
    EXPECT_EQ(tree.root->left->right->data, 13);
    EXPECT_EQ(tree.root->left->left->left->data, 2);
    EXPECT_EQ(tree.root->left->left->right->data, 10);
    EXPECT_EQ(tree.root->left->right->left->data, 12);
    EXPECT_EQ(tree.root->left->right->right->data, 14);
    EXPECT_EQ(tree.root->right->data, 65);
    EXPECT_EQ(tree.root->right->left->data, 63);
    EXPECT_EQ(tree.root->right->right->data, 67);
    EXPECT_EQ(tree.root->right->left->left->data, 62);
    EXPECT_EQ(tree.root->right->left->right->data, 64);
    EXPECT_EQ(tree.root->right->right->left->data, 66);
    EXPECT_EQ(tree.root->right->right->right->data, 68);
}

/// \brief Test the building of a binary tree, with edge cases
TEST(binary_tree, build_edge_cases) {
    bardrix::binary_tree<int> tree(int_predicate);

    int values[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    tree.build(values, 0);

    EXPECT_EQ(tree.root, nullptr);

    // 1 ->
    //  1
    tree.build(1);

    EXPECT_EQ(tree.root->data, 1);

    // 1, 2 ->
    //   2
    //  /
    // 1
    tree.build(1, 2);

    EXPECT_EQ(tree.root->data, 2);
    EXPECT_EQ(tree.root->left->data, 1);

    // 2, 1 ->
    //   2
    //  /
    // 1
    tree.build(2, 1);

    EXPECT_EQ(tree.root->data, 1);
    EXPECT_EQ(tree.root->left->data, 2);

    // 3, 2, 1 ->
    //   2
    //  / \
    // 3   1
    tree.build(3, 2, 1);

    EXPECT_EQ(tree.root->data, 2);
    EXPECT_EQ(tree.root->left->data, 3);
    EXPECT_EQ(tree.root->right->data, 1);

    // insert 3, 2, 1 ->
    //     2
    //    / \
    //   3   1
    //  /     \
    // 1       3
    //          \
    //           2

    tree.insert(3, 2, 1);

    EXPECT_EQ(tree.root->data, 2);
    EXPECT_EQ(tree.root->left->data, 3);
    EXPECT_EQ(tree.root->right->data, 1);
    EXPECT_EQ(tree.root->left->left->data, 1);
    EXPECT_EQ(tree.root->right->right->data, 3);
    EXPECT_EQ(tree.root->right->right->left->data, 2);
}

/// \brief Test the rebuild method of a binary tree
TEST(binary_tree, rebuild) {
    bardrix::binary_tree<int> tree(int_predicate);

    // 5, 7, 3, 1, 4, 6, 8 ->
    //       1
    //     /   \
    //    3     4
    //   / \   / \
    //  5   7 6   8
    tree.build(5, 7, 3, 1, 4, 6, 8);

    EXPECT_EQ(tree.root->data, 1);
    EXPECT_EQ(tree.root->left->data, 7);
    EXPECT_EQ(tree.root->right->data, 6);
    EXPECT_EQ(tree.root->left->left->data, 5);
    EXPECT_EQ(tree.root->left->right->data, 3);
    EXPECT_EQ(tree.root->right->left->data, 4);
    EXPECT_EQ(tree.root->right->right->data, 8);

    // 5, 7, 3, 1, 4, 6, 8 ->
    //       1
    //     /   \
    //    3     4
    //   / \   / \
    //  5   7 6   8
    tree.rebuild();

    EXPECT_EQ(tree.root->data, 1);
    EXPECT_EQ(tree.root->left->data, 7);
    EXPECT_EQ(tree.root->right->data, 6);
    EXPECT_EQ(tree.root->left->left->data, 5);
    EXPECT_EQ(tree.root->left->right->data, 3);
    EXPECT_EQ(tree.root->right->left->data, 4);
    EXPECT_EQ(tree.root->right->right->data, 8);

    tree.clear();

    // 5, 3, 6, 7, 8 ->
    //          5
    //         / \
    //        3   6
    //             \
    //              7
    //               \
    //                8
    tree.insert(5, 3, 6, 7, 8);

    EXPECT_EQ(tree.root->data, 5);
    EXPECT_EQ(tree.root->left->data, 3);
    EXPECT_EQ(tree.root->right->data, 6);
    EXPECT_EQ(tree.root->right->right->data, 7);
    EXPECT_EQ(tree.root->right->right->right->data, 8);

    // 3, 5, 6, 7, 8 ->
    //         6
    //        / \
    //       5   8
    //      /   /
    //     3   7
    tree.rebuild();

    EXPECT_EQ(tree.root->data, 6);
    EXPECT_EQ(tree.root->left->data, 5);
    EXPECT_EQ(tree.root->right->data, 8);
    EXPECT_EQ(tree.root->left->left->data, 3);
    EXPECT_EQ(tree.root->right->left->data, 7);

    tree.clear();

    // 2, 9, 10, 12, 11, 14, 13, 24, 62, 63, 64, 65, 66, 67, 68 ->
    //            2
    //             \
    //              9
    //               \
    //                10
    //                 \
    //                  12
    //                /    \
    //               11    14
    //                    /  \
    //                   13  24
    //                         \
    //                         62
    //                          \
    //                           63
    //                            \
    //                             64
    //                              \
    //                               65
    //                                \
    //                                 66
    //                                  \
    //                                   67
    //                                    \
    //                                     68
    tree.insert(2, 9, 10, 12, 11, 14, 13, 24, 62, 63, 64, 65, 66, 67, 68);

    EXPECT_EQ(tree.root->data, 2);
    EXPECT_EQ(tree.root->right->data, 9);
    EXPECT_EQ(tree.root->right->right->data, 10);
    EXPECT_EQ(tree.root->right->right->right->data, 12);
    EXPECT_EQ(tree.root->right->right->right->left->data, 11);
    EXPECT_EQ(tree.root->right->right->right->right->data, 14);
    EXPECT_EQ(tree.root->right->right->right->right->left->data, 13);
    EXPECT_EQ(tree.root->right->right->right->right->right->data, 24);
    EXPECT_EQ(tree.root->right->right->right->right->right->right->data, 62);
    EXPECT_EQ(tree.root->right->right->right->right->right->right->right->data, 63);
    EXPECT_EQ(tree.root->right->right->right->right->right->right->right->right->data, 64);
    EXPECT_EQ(tree.root->right->right->right->right->right->right->right->right->right->data, 65);
    EXPECT_EQ(tree.root->right->right->right->right->right->right->right->right->right->right->data, 66);
    EXPECT_EQ(tree.root->right->right->right->right->right->right->right->right->right->right->right->data, 67);
    EXPECT_EQ(tree.root->right->right->right->right->right->right->right->right->right->right->right->right->data, 68);

    // 2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68 ->
    //            _____24_____
    //          /              \
    //        11               65
    //      /    \           /    \
    //     9      13       63     67
    //    / \     / \     / \    /  \
    //   2  10   12 14   62 64  66  68
    tree.rebuild();

    EXPECT_EQ(tree.root->data, 24);
    EXPECT_EQ(tree.root->left->data, 11);
    EXPECT_EQ(tree.root->left->left->data, 9);
    EXPECT_EQ(tree.root->left->right->data, 13);
    EXPECT_EQ(tree.root->left->left->left->data, 2);
    EXPECT_EQ(tree.root->left->left->right->data, 10);
    EXPECT_EQ(tree.root->left->right->left->data, 12);
    EXPECT_EQ(tree.root->left->right->right->data, 14);
    EXPECT_EQ(tree.root->right->data, 65);
    EXPECT_EQ(tree.root->right->left->data, 63);
    EXPECT_EQ(tree.root->right->right->data, 67);
    EXPECT_EQ(tree.root->right->left->left->data, 62);
    EXPECT_EQ(tree.root->right->left->right->data, 64);
    EXPECT_EQ(tree.root->right->right->left->data, 66);
    EXPECT_EQ(tree.root->right->right->right->data, 68);
}

/// \brief Test the clear method of a binary tree
TEST(binary_tree, clear) {
    bardrix::binary_tree<int> tree(int_predicate);

    // 1, 3, 4, 5, 6, 7, 8 ->
    //       5
    //     /   \
    //    3     7
    //   / \   / \
    //  1   4 6   8
    tree.build(1, 3, 4, 5, 6, 7, 8);

    tree.clear();

    EXPECT_EQ(tree.root, nullptr);

    // 2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68 ->
    //            _____24_____
    //          /              \
    //        11               65
    //      /    \           /    \
    //     9      13       63     67
    //    / \     / \     / \    /  \
    //   2  10   12 14   62 64  66  68
    tree.build(2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68);

    tree.clear();

    EXPECT_EQ(tree.root, nullptr);
}

/// \brief Test the insertion of a single value in a binary tree
TEST(binary_tree, insert_array) {
    bardrix::binary_tree<int> tree(int_predicate);

    int values[] = { 5, 6, 3, 7 };

    // 5, 6, 3, 7 ->
    //       5
    //     /   \
    //    3     6
    //           \
    //            7
    tree.insert(values, sizeof values / sizeof values[0]);

    EXPECT_EQ(tree.root->data, 5);
    EXPECT_EQ(tree.root->left->data, 3);
    EXPECT_EQ(tree.root->right->data, 6);
    EXPECT_EQ(tree.root->right->right->data, 7);

    tree.clear();
    // 5, 6, 3, 7 ->
    //       5
    //     /   \
    //    3     6
    //           \
    //            7
    std::vector<int> values2 = { 5, 6, 3, 7 };
    tree.insert(values2.data(), values2.size());

    EXPECT_EQ(tree.root->data, 5);
    EXPECT_EQ(tree.root->left->data, 3);
    EXPECT_EQ(tree.root->right->data, 6);
    EXPECT_EQ(tree.root->right->right->data, 7);
}

/// \brief Test the insertion of a single value in a binary tree
TEST(binary_tree, insert_single_value) {
    bardrix::binary_tree<int> tree(int_predicate);

    // 5, 6, 3, 7 ->
    //       5
    //     /   \
    //    3     6
    //           \
    //            7
    tree.insert(5);
    tree.insert(6);
    tree.insert(3);
    tree.insert(7);

    EXPECT_EQ(tree.root->data, 5);
    EXPECT_EQ(tree.root->left->data, 3);
    EXPECT_EQ(tree.root->right->data, 6);
    EXPECT_EQ(tree.root->right->right->data, 7);
}

/// \brief Test the insertion of iterators in a binary tree
TEST(binary_tree, insert_iterators) {
    bardrix::binary_tree<int> tree(int_predicate);

    int values[] = { 5, 6, 3, 7 };

    // 5, 6, 3, 7 ->
    //       5
    //     /   \
    //    3     6
    //           \
    //            7
    tree.insert(values, values + sizeof values / sizeof values[0]);

    EXPECT_EQ(tree.root->data, 5);
    EXPECT_EQ(tree.root->left->data, 3);
    EXPECT_EQ(tree.root->right->data, 6);
    EXPECT_EQ(tree.root->right->right->data, 7);

    tree.clear();
    // 5, 6, 3, 7 ->
    //       5
    //     /   \
    //    3     6
    //           \
    //            7
    std::vector<int> values2 = { 5, 6, 3, 7 };
    tree.insert(values2.begin(), values2.end());

    EXPECT_EQ(tree.root->data, 5);
    EXPECT_EQ(tree.root->left->data, 3);
    EXPECT_EQ(tree.root->right->data, 6);
    EXPECT_EQ(tree.root->right->right->data, 7);
}

/// \brief Test the insertion of multiple values in a binary tree
TEST(binary_tree, insert_multiple_values) {
    bardrix::binary_tree<int> tree(int_predicate);

    // 1, 3, 4, 5, 6, 7, 8 ->
    //       5
    //     /   \
    //    3     7
    //   / \   / \
    //  1   4 6   8
    tree.insert(5, 3, 7, 1, 4, 6, 8);

    EXPECT_EQ(tree.root->data, 5);
    EXPECT_EQ(tree.root->left->data, 3);
    EXPECT_EQ(tree.root->right->data, 7);
    EXPECT_EQ(tree.root->left->left->data, 1);
    EXPECT_EQ(tree.root->left->right->data, 4);
    EXPECT_EQ(tree.root->right->left->data, 6);
    EXPECT_EQ(tree.root->right->right->data, 8);

    tree.clear();
    // 2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68 ->
    //         24
    //       /    \
    //      9      62
    //     / \       \
    //    2  12       63
    //      /  \        \
    //     10  14        66
    //     /   /        / \
    //    11  13       64  68
    //                 /    \
    //                65     67
    tree.insert(24, 9, 62, 2, 12, 63, 66, 10, 14, 64, 68, 11, 13, 65, 67);

    EXPECT_EQ(tree.root->data, 24);
    EXPECT_EQ(tree.root->left->data, 9);
    EXPECT_EQ(tree.root->left->left->data, 2);
    EXPECT_EQ(tree.root->left->right->data, 12);
    EXPECT_EQ(tree.root->left->right->left->data, 10);
    EXPECT_EQ(tree.root->left->right->right->data, 14);
    EXPECT_EQ(tree.root->left->right->left->right->data, 11);
    EXPECT_EQ(tree.root->left->right->right->left->data, 13);
    EXPECT_EQ(tree.root->right->data, 62);
    EXPECT_EQ(tree.root->right->right->data, 63);
    EXPECT_EQ(tree.root->right->right->right->data, 66);
    EXPECT_EQ(tree.root->right->right->right->left->data, 64);
    EXPECT_EQ(tree.root->right->right->right->right->data, 68);
    EXPECT_EQ(tree.root->right->right->right->left->right->data, 65);
    EXPECT_EQ(tree.root->right->right->right->right->left->data, 67);
}

/// \brief Test the contains method of a binary tree
TEST(binary_tree, contains) {
    bardrix::binary_tree<int> tree(int_predicate);

    // 1, 3, 4, 5, 6, 7, 8 ->
    //       5
    //     /   \
    //    3     7
    //   / \   / \
    //  1   4 6   8
    tree.build(1, 3, 4, 5, 6, 7, 8);

    EXPECT_TRUE(tree.contains(1));
    EXPECT_TRUE(tree.contains(3));
    EXPECT_TRUE(tree.contains(4));
    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(6));
    EXPECT_TRUE(tree.contains(7));
    EXPECT_TRUE(tree.contains(8));

    EXPECT_FALSE(tree.contains(0));
    EXPECT_FALSE(tree.contains(2));
    EXPECT_FALSE(tree.contains(9));
    EXPECT_FALSE(tree.contains(-9));

    // 2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68 ->
    //            _____24_____
    //          /              \
    //        11               65
    //      /    \           /    \
    //     9      13       63     67
    //    / \     / \     / \    /  \
    //   2  10   12 14   62 64  66  68
    tree.build(2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68);

    EXPECT_TRUE(tree.contains(2));
    EXPECT_TRUE(tree.contains(9));
    EXPECT_TRUE(tree.contains(10));
    EXPECT_TRUE(tree.contains(11));
    EXPECT_TRUE(tree.contains(12));
    EXPECT_TRUE(tree.contains(13));
    EXPECT_TRUE(tree.contains(14));
    EXPECT_TRUE(tree.contains(24));
    EXPECT_TRUE(tree.contains(62));
    EXPECT_TRUE(tree.contains(63));

    EXPECT_FALSE(tree.contains(0));
    EXPECT_FALSE(tree.contains(1));
    EXPECT_FALSE(tree.contains(90));
    EXPECT_FALSE(tree.contains(-24));
}

/// \brief Test the find method of a binary tree
TEST(binary_tree, find) {
    bardrix::binary_tree<int> tree(int_predicate);

    // 1, 3, 4, 5, 6, 7, 8 ->
    //       5
    //     /   \
    //    3     7
    //   / \   / \
    //  1   4 6   8
    tree.build(1, 3, 4, 5, 6, 7, 8);

    EXPECT_TRUE(tree.find(1));
    EXPECT_EQ(tree.find(1)->data, 1);

    EXPECT_TRUE(tree.find(3));
    EXPECT_EQ(tree.find(3)->data, 3);

    EXPECT_TRUE(tree.find(4));
    EXPECT_EQ(tree.find(4)->data, 4);

    EXPECT_TRUE(tree.find(5));
    EXPECT_EQ(tree.find(5)->data, 5);

    EXPECT_TRUE(tree.find(6));
    EXPECT_EQ(tree.find(6)->data, 6);

    EXPECT_TRUE(tree.find(7));
    EXPECT_EQ(tree.find(7)->data, 7);

    EXPECT_TRUE(tree.find(8));
    EXPECT_EQ(tree.find(8)->data, 8);

    EXPECT_FALSE(tree.find(0));
    EXPECT_FALSE(tree.find(2));
    EXPECT_FALSE(tree.find(9));
    EXPECT_FALSE(tree.find(-9));

    // 2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68 ->
    //            _____24_____
    //          /              \
    //        11               65
    //      /    \           /    \
    //     9      13       63     67
    //    / \     / \     / \    /  \
    //   2  10   12 14   62 64  66  68
    tree.build(2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68);

    EXPECT_TRUE(tree.find(2));
    EXPECT_EQ(tree.find(2)->data, 2);

    EXPECT_TRUE(tree.find(63));
    EXPECT_EQ(tree.find(63)->data, 63);

    EXPECT_TRUE(tree.find(68));
    EXPECT_EQ(tree.find(68)->data, 68);

    EXPECT_FALSE(tree.find(0));
    EXPECT_FALSE(tree.find(1));
    EXPECT_FALSE(tree.find(90));
    EXPECT_FALSE(tree.find(-24));
}

/// \brief Test the is_empty method of a binary tree
TEST(binary_tree, is_empty) {
    bardrix::binary_tree<int> tree(int_predicate);

    EXPECT_TRUE(tree.is_empty());

    tree.build(1, 3, 4, 5, 6, 7, 8);

    EXPECT_FALSE(tree.is_empty());

    tree.clear();

    EXPECT_TRUE(tree.is_empty());
}

/// \brief Test the traverse_in_order method of a binary tree
TEST(binary_tree, traverse_in_order) {
    bardrix::binary_tree<int> tree(int_predicate);

    // 1, 3, 4, 5, 6, 7, 8 ->
    //       5
    //     /   \
    //    3     7
    //   / \   / \
    //  1   4 6   8
    tree.build(1, 3, 4, 5, 6, 7, 8);

    std::vector<int> values;
    tree.traverse_in_order([&values](int value) { values.push_back(value); });

    EXPECT_EQ(values.size(), 7);
    EXPECT_EQ(values, std::vector<int>({ 1, 3, 4, 5, 6, 7, 8 }));

    // 2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68 ->
    //            _____24_____
    //          /              \
    //        11               65
    //      /    \           /    \
    //     9      13       63     67
    //    / \     / \     / \    /  \
    //   2  10   12 14   62 64  66  68
    tree.build(2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68);

    values.clear();
    tree.traverse_in_order([&values](int value) { values.push_back(value); });

    EXPECT_EQ(values.size(), 15);
    EXPECT_EQ(values, std::vector<int>({ 2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68 }));
}

/// \brief Test the traverse_pre_order method of a binary tree
TEST(binary_tree, traverse_pre_order) {
    bardrix::binary_tree<int> tree(int_predicate);

    // 1, 3, 4, 5, 6, 7, 8 ->
    //       5
    //     /   \
    //    3     7
    //   / \   / \
    //  1   4 6   8
    tree.build(1, 3, 4, 5, 6, 7, 8);

    std::vector<int> values;
    tree.traverse_pre_order([&values](int value) { values.push_back(value); });

    EXPECT_EQ(values.size(), 7);
    EXPECT_EQ(values, std::vector<int>({ 5, 3, 1, 4, 7, 6, 8 }));

    // 2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68 ->
    //            _____24_____
    //          /              \
    //        11               65
    //      /    \           /    \
    //     9      13       63     67
    //    / \     / \     / \    /  \
    //   2  10   12 14   62 64  66  68
    tree.build(2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68);

    values.clear();
    tree.traverse_pre_order([&values](int value) { values.push_back(value); });

    EXPECT_EQ(values.size(), 15);
    EXPECT_EQ(values, std::vector<int>({ 24, 11, 9, 2, 10, 13, 12, 14, 65, 63, 62, 64, 67, 66, 68 }));
}

/// \brief Test the traverse_post_order method of a binary tree
TEST(binary_tree, traverse_post_order) {
    bardrix::binary_tree<int> tree(int_predicate);

    // 1, 3, 4, 5, 6, 7, 8 ->
    //       5
    //     /   \
    //    3     7
    //   / \   / \
    //  1   4 6   8
    tree.build(1, 3, 4, 5, 6, 7, 8);

    std::vector<int> values;
    tree.traverse_post_order([&values](int value) { values.push_back(value); });

    EXPECT_EQ(values.size(), 7);
    EXPECT_EQ(values, std::vector<int>({ 1, 4, 3, 6, 8, 7, 5 }));

    // 2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68 ->
    //            _____24_____
    //          /              \
    //        11               65
    //      /    \           /    \
    //     9      13       63     67
    //    / \     / \     / \    /  \
    //   2  10   12 14   62 64  66  68
    tree.build(2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68);

    values.clear();
    tree.traverse_post_order([&values](int value) { values.push_back(value); });

    EXPECT_EQ(values.size(), 15);
    EXPECT_EQ(values, std::vector<int>({ 2, 10, 9, 12, 14, 13, 11, 62, 64, 63, 66, 68, 67, 65, 24 }));
}

/// \brief Test the find_min method of a binary tree
TEST(binary_tree, find_min) {
    bardrix::binary_tree<int> tree(int_predicate);

    // 1, 3, 4, 5, 6, 7, 8 ->
    //            5
    //          /   \
    //         3     7
    //        / \   / \
    // (min) 1   4 6   8
    tree.build(1, 3, 4, 5, 6, 7, 8);

    EXPECT_TRUE(tree.find_min());
    EXPECT_EQ(tree.find_min()->data, 1);

    // 2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68 ->
    //                 _____24_____
    //               /              \
    //             11               65
    //           /    \           /    \
    //          9      13       63     67
    //         / \     / \     / \    /  \
    //  (min) 2  10   12 14   62 64  66  68
    tree.build(2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68);

    EXPECT_TRUE(tree.find_min());
    EXPECT_EQ(tree.find_min()->data, 2);
}

/// \brief Test the find_max method of a binary tree
TEST(binary_tree, find_max) {
    bardrix::binary_tree<int> tree(int_predicate);

    // 1, 3, 4, 5, 6, 7, 8 ->
    //            5
    //          /   \
    //         3     7
    //        / \   / \
    //       1   4 6   8
    //                 \
    //                  9 (max)
    tree.build(1, 3, 4, 5, 6, 7, 8);

    EXPECT_TRUE(tree.find_max());
    EXPECT_EQ(tree.find_max()->data, 8);

    // 2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68 ->
    //                 _____24_____
    //               /              \
    //             11               65
    //           /    \           /    \
    //          9      13       63     67
    //         / \     / \     / \    /  \
    //        2  10   12 14   62 64  66  68
    //                                  /
    //                                 69 (max)
    tree.build(2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68);

    EXPECT_TRUE(tree.find_max());
    EXPECT_EQ(tree.find_max()->data, 68);
}

/// \brief Test the remove method of a binary tree
TEST(binary_tree, remove) {
    bardrix::binary_tree<int> tree(int_predicate);

    // 1, 2, 3, 4, 5, 6, 7, 8 ->
    //           5
    //         /   \
    //        3     7
    //       / \   / \
    //      2  4  6  8
    //     /
    //    1
    tree.build(1, 2, 3, 4, 5, 6, 7, 8);

    // This will be turned into:
    //           5
    //         /   \
    //        4     7
    //       /     / \
    //      2     6  8
    //     /
    //    1
    EXPECT_TRUE(tree.remove(3));

    // 2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68 ->
    //                 _____24_____
    //               /              \
    //             11               65
    //           /    \           /    \
    //          9      13       63     67
    //         / \     / \     / \    /  \
    //        2  10   12 14   62 64  66  68
    tree.build(2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68);

    // This will be turned into:
    //                 _____24_____
    //               /              \
    //             12               66
    //           /    \           /    \
    //          9      14       63     67
    //         / \             / \       \
    //        2  10           62 64      68
    EXPECT_TRUE(tree.remove(11));
    EXPECT_TRUE(tree.remove(65));
    EXPECT_TRUE(tree.remove(13));
    EXPECT_FALSE(tree.remove(20));
    EXPECT_FALSE(tree.remove(0));
    EXPECT_FALSE(tree.remove(-63));

    EXPECT_EQ(tree.root->data, 24);
    EXPECT_EQ(tree.root->left->data, 12);
    EXPECT_EQ(tree.root->left->left->data, 9);
    EXPECT_EQ(tree.root->left->right->data, 14);
    EXPECT_EQ(tree.root->left->left->left->data, 2);
    EXPECT_EQ(tree.root->left->left->right->data, 10);
    EXPECT_EQ(tree.root->right->data, 66);
    EXPECT_EQ(tree.root->right->left->data, 63);
    EXPECT_EQ(tree.root->right->right->data, 67);
    EXPECT_EQ(tree.root->right->left->left->data, 62);
    EXPECT_EQ(tree.root->right->right->right->data, 68);

    // 2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68 ->
    //                 _____24_____
    //               /              \
    //             11               65
    //           /    \           /    \
    //          9      13       63     67
    //         / \     / \     / \    /  \
    //        2  10   12 14   62 64  66  68
    tree.build(2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68);

    // This will be turned into:
    //                 _____14_____
    //               /              \
    //             11               65
    //           /    \           /    \
    //          9      13       63     67
    //         / \     /       / \    /  \
    //        2  10   12      62 64  66  68

    EXPECT_TRUE(tree.remove(24, true));

    EXPECT_EQ(tree.root->data, 14);
    EXPECT_EQ(tree.root->left->data, 11);
    EXPECT_EQ(tree.root->left->left->data, 9);
    EXPECT_EQ(tree.root->left->right->data, 13);
    EXPECT_EQ(tree.root->left->left->left->data, 2);
    EXPECT_EQ(tree.root->left->left->right->data, 10);
    EXPECT_EQ(tree.root->left->right->left->data, 12);
    EXPECT_EQ(tree.root->right->data, 65);
    EXPECT_EQ(tree.root->right->left->data, 63);
    EXPECT_EQ(tree.root->right->right->data, 67);
    EXPECT_EQ(tree.root->right->left->left->data, 62);
    EXPECT_EQ(tree.root->right->right->right->data, 68);
}

/// \brief Test the remove method of a binary tree, with edge cases
TEST(binary_tree, remove_edge_cases) {
    bardrix::binary_tree<int> tree(int_predicate);

    tree.build(1);

    EXPECT_TRUE(tree.remove(1));
    EXPECT_EQ(tree.root, nullptr);

    // 1, 2, 3, 4 ->
    //     3
    //    / \
    //   2   4
    //  /
    // 1
    tree.build(1, 2, 3, 4);
    EXPECT_TRUE(tree.remove(2));
    EXPECT_EQ(tree.root->data, 3);
    EXPECT_EQ(tree.root->left->data, 1);
    EXPECT_EQ(tree.root->right->data, 4);

    tree.build(1, 2, 3, 4);
    EXPECT_TRUE(tree.remove(3));
    EXPECT_EQ(tree.root->data, 4);
    EXPECT_EQ(tree.root->left->data, 2);
    EXPECT_EQ(tree.root->left->left->data, 1);


    tree.build(1, 2, 3, 4);
    EXPECT_TRUE(tree.remove(3, true));
    EXPECT_EQ(tree.root->data, 2);
    EXPECT_EQ(tree.root->left->data, 1);
    EXPECT_EQ(tree.root->right->data, 4);
}

/// \brief Test the height method of a binary tree
TEST(binary_tree, height) {
    bardrix::binary_tree<int> tree(int_predicate);

    // 1, 2, 3, 4, 5, 6, 7, 8 ->
    //           5
    //         /   \
    //        3     7
    //       / \   / \
    //      2  4  6  8
    //     /
    //    1
    tree.build(1, 2, 3, 4, 5, 6, 7, 8);

    EXPECT_EQ(tree.height(), 4);

    // 2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68 ->
    //                 _____24_____
    //               /              \
    //             11               65
    //           /    \           /    \
    //          9      13       63     67
    //         / \     / \     / \    /  \
    //        2  10   12 14   62 64  66  68
    tree.build(2, 9, 10, 11, 12, 13, 14, 24, 62, 63, 64, 65, 66, 67, 68);

    EXPECT_EQ(tree.height(), 4);
}

// BVH TREE

bool includes_all_shapes(const std::vector<const bardrix::shape*>& hits, const std::vector<const bardrix::shape*>& expecteds) {
    return std::all_of(expecteds.begin(), expecteds.end(), [&hits](const bardrix::shape* shape) {
        return std::find(hits.begin(), hits.end(), shape) != hits.end();
    });
}

/// \brief Test the construction of a BVH tree
TEST(bvh_tree, construct_longest_axis) {
    bardrix::bvh_tree bvh;

    std::shared_ptr<bardrix::sphere> shapes[] {
            std::make_shared<bardrix::sphere>(bardrix::point3(-7, 5, -2), 2),
            std::make_shared<bardrix::sphere>(bardrix::point3(-7.39, -6.33, 7.38), 10)
    };

    std::vector<std::shared_ptr<bardrix::shape>> shapes2 {
            std::make_shared<bardrix::sphere>(bardrix::point3(-3.3, -8.96, -4), 0.8),
            std::make_shared<bardrix::sphere>(bardrix::point3(8.66, -8.60, 0), 10),
    };

    bvh.construct_longest_axis<bardrix::sphere>(shapes, 0);
    bvh.construct_longest_axis(shapes, sizeof shapes / sizeof shapes[0]);

    std::vector<const bardrix::shape*> hits;
    bvh.intersections(bardrix::ray(bardrix::point3(26.03874, 31.6748, 2.25401), bardrix::point3(-14.64, -18.48, -1.6)), hits);
    EXPECT_EQ(hits.size(), 1);
    EXPECT_TRUE(includes_all_shapes(hits, std::vector<const bardrix::shape*>({ shapes[1].get() })));

    bvh.construct_longest_axis(shapes2.begin(), shapes2.end());
    bvh.construct_longest_axis(shapes2.begin(), shapes2.begin());
    bvh.construct_longest_axis(shapes2.data(), 0);
}

/// \brief Test the intersect method of a BVH tree
TEST(bvh_tree, intersect) {
    bardrix::bvh_tree bvh;

    std::vector<std::shared_ptr<bardrix::shape>> shapes{
            std::make_shared<bardrix::sphere>(bardrix::point3(-7, 5, -2), 2),            // 0
            std::make_shared<bardrix::sphere>(bardrix::point3(-7.39, -6.33, 7.38), 0.2), // 1
            std::make_shared<bardrix::sphere>(bardrix::point3(-3.3, -8.96, -4), 0.8),    // 2
            std::make_shared<bardrix::sphere>(bardrix::point3(8.66, -8.60, 0), 1),       // 3
            std::make_shared<bardrix::sphere>(bardrix::point3(4.39, 6.26, 0), 1.2),      // 4
            std::make_shared<bardrix::sphere>(bardrix::point3(8.48, 3.98, 2.15), 0.4),   // 5
            std::make_shared<bardrix::sphere>(bardrix::point3(9.30, -6.54, 3), 1.2),     // 6
            std::make_shared<bardrix::sphere>(bardrix::point3(-3.60, 7.66, 0), 0.5),     // 7
            std::make_shared<bardrix::sphere>(bardrix::point3(-5.52, -8.01, 0), 1.6),    // 8
            std::make_shared<bardrix::sphere>(bardrix::point3(-2.64, -12.15, 7.37), 4),  // 9
            std::make_shared<bardrix::sphere>(bardrix::point3(1.30, 0.01, 0), 1)         // 10
    };

    bvh.construct_longest_axis(shapes.begin(), shapes.end());
    std::vector<const bardrix::shape*> hits;

    bvh.intersections(bardrix::ray(bardrix::point3(26.03874, 31.6748, 2.25401), bardrix::point3(-14.64, -18.48, -1.6)),
                  hits);
    EXPECT_EQ(hits.size(), 3);
    EXPECT_TRUE(includes_all_shapes(hits, std::vector<const bardrix::shape*>({ shapes[4].get(), shapes[8].get(), shapes[10].get() })));

    hits.clear();
    bvh.intersections(bardrix::ray(bardrix::point3(-1.69, -29.97, 13.43), bardrix::point3(-11.82, 11.13, 2.95)), hits);
    EXPECT_EQ(hits.size(), 2);
    EXPECT_TRUE(includes_all_shapes(hits, std::vector<const bardrix::shape*>({ shapes[1].get(), shapes[9].get() })));

    hits.clear();
    bvh.intersections(bardrix::ray(bardrix::point3(-1.69, -29.97, 13.43), bardrix::point3(-7.26, 6.29, -2.91)), hits);
    EXPECT_EQ(hits.size(), 2);
    EXPECT_TRUE(includes_all_shapes(hits, std::vector<const bardrix::shape*>({ shapes[0].get(), shapes[9].get() })));
}

/// \brief Test the intersect method of a BVH tree
TEST(bvh_tree, intersect_2) {
    bardrix::bvh_tree bvh;

    std::vector<std::shared_ptr<bardrix::sphere>> spheres{
            std::make_shared<bardrix::sphere>(bardrix::sphere(bardrix::point3{ 0, 0, 0 }, 1)),
            std::make_shared<bardrix::sphere>(bardrix::sphere(bardrix::point3{ 1, -1, 1 }, 1)),
            std::make_shared<bardrix::sphere>(bardrix::sphere(bardrix::point3{ 2, 6, 2 }, 1))
    };

    bvh.construct_longest_axis(spheres.begin(), spheres.end());
    std::vector<const bardrix::shape*> hits;
    bvh.intersections(bardrix::ray{ bardrix::point3{ 5, 6, 7 }, bardrix::point3{ -3.11, -3, -2 }}, hits);
    EXPECT_EQ(hits.size(), 1);
    EXPECT_TRUE(includes_all_shapes(hits, std::vector<const bardrix::shape*>({ spheres[0].get() })));
}

/// \brief Test the intersect method of a BVH tree
TEST(bvh_tree, intersect_3) {
    bardrix::bvh_tree bvh;

    std::vector<std::shared_ptr<bardrix::shape>> shapes{
            std::make_shared<bardrix::sphere>(bardrix::sphere(bardrix::point3{ 1, 0, 0 }, 1)), // 0
            std::make_shared<bardrix::sphere>(bardrix::sphere(bardrix::point3{ 0, 1, 0 }, 2)), // 1
            std::make_shared<bardrix::sphere>(bardrix::sphere(bardrix::point3{ 0, 0, 1 }, 3))  // 2
    };

    bvh.construct_longest_axis(shapes.begin(), shapes.end());
    std::vector<const bardrix::shape*> hits;

    bvh.intersections(bardrix::ray{ bardrix::point3{ 3, 4, 5 }, bardrix::point3{ -2, -6, 1 }}, hits);
    EXPECT_EQ(hits.size(), 1);
    EXPECT_TRUE(includes_all_shapes(hits, std::vector<const bardrix::shape*>({ shapes[2].get() })));

    hits.clear();
    bvh.intersections(bardrix::ray{ bardrix::point3{ 3, 4, 5 }, bardrix::point3{ -1, 1, 1 }}, hits);
    EXPECT_EQ(hits.size(), 2);
    EXPECT_TRUE(includes_all_shapes(hits, std::vector<const bardrix::shape*>({ shapes[1].get(), shapes[2].get() })));

    hits.clear();
    bvh.intersections(bardrix::ray{ bardrix::point3{ 3, 4, 5 }, bardrix::point3{ 1, 0, 1 }}, hits);
    EXPECT_EQ(hits.size(), 3);
    EXPECT_TRUE(includes_all_shapes(hits, std::vector<const bardrix::shape*>({ shapes[0].get(), shapes[1].get(), shapes[2].get() })));

    hits.clear();
    bvh.intersections(bardrix::ray{ bardrix::point3{ 3, 4, 5 }, bardrix::point3{ 3, 2, -3 }}, hits);
    EXPECT_EQ(hits.size(), 0);
}

/// \brief Test the intersect method of a BVH tree with edge cases
TEST(bvh_tree, intersect_edge_cases) {
    bardrix::bvh_tree bvh;

    std::shared_ptr<bardrix::shape> shapes[]{
            std::make_shared<bardrix::sphere>(bardrix::sphere(bardrix::point3{ 0, 0, 0 }, 0)), // 0
            std::make_shared<bardrix::sphere>(bardrix::sphere(bardrix::point3{ 0, 0, 0 }, 0)), // 1
    };

    bvh.construct_longest_axis(shapes, sizeof shapes / sizeof shapes[0]);
    std::vector<const bardrix::shape*> hits;

    bvh.intersections(bardrix::ray{ bardrix::point3{ 0, 0, 0 }, bardrix::vector3{ 1, 1, 1 }}, hits);
    EXPECT_EQ(hits.size(), 2);
    EXPECT_TRUE(includes_all_shapes(hits, std::vector<const bardrix::shape*>({ shapes[0].get(), shapes[1].get() })));

    hits.clear();
    bvh.intersections(bardrix::ray{ bardrix::point3{ 1, 0, 0 }, bardrix::vector3{ 0, 0, 0 }}, hits);
    EXPECT_EQ(hits.size(), 0);

    hits.clear();
    bvh.intersections(bardrix::ray{ bardrix::point3{ 1, 0, 0 }, bardrix::vector3{ -1, 0, 0 }}, hits);
    EXPECT_EQ(hits.size(), 2);
    EXPECT_TRUE(includes_all_shapes(hits, std::vector<const bardrix::shape*>({ shapes[0].get(), shapes[1].get() })));
}
