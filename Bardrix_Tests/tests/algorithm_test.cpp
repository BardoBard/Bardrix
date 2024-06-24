//
// Created by Bardio on 22/06/2024.
//

#include <bardrix/algorithm.h>

bool int_predicate(int a, int b) {
    return a < b;
}

class sphere : public bardrix::shape {
private:
    bardrix::point3 position_;
    bardrix::material material_;
    double radius_;

public:
    sphere(bardrix::point3 position, double radius) : position_(std::move(position)), radius_(radius > 0 ? radius : 0),
                                                      material_() {}

    sphere() : position_(), radius_(0), material_() {}

    NODISCARD bardrix::vector3 normal_at(const bardrix::point3& point) const override {
        assert(false);
        return {};
    }

    NODISCARD std::optional<bardrix::point3> intersection(const bardrix::ray& ray) const override {
        assert(false);
        return std::nullopt;
    }

    void set_position(const bardrix::point3& position) override { position_ = position; }

    NODISCARD const bardrix::point3& get_position() const override { return position_; }

    NODISCARD const bardrix::material& get_material() const override {
        assert(false);
        return material_;
    }

    void set_material(const bardrix::material& material) override {
        assert(false);
        this->material_ = material;
    }

    void set_radius(double radius) { this->radius_ = radius > 0 ? radius : 0; }

    NODISCARD double get_radius() const { return radius_; }

    NODISCARD bardrix::bounding_box bounding_box() const override {
        return { position_ - bardrix::vector3(radius_, radius_, radius_),
                 position_ + bardrix::vector3(radius_, radius_, radius_) };
    }

};

/// \brief Test the building of a binary tree, with an array of values
TEST(algorithm, binary_tree_build_array) {
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
TEST(algorithm, binary_tree_build_multiple_values) {
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
TEST(algorithm, binary_tree_build_edge_cases) {
    bardrix::binary_tree<int> tree(int_predicate);

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

    tree.insert(3, 2, 1); // Ignored

    EXPECT_EQ(tree.root->data, 2);
    EXPECT_EQ(tree.root->left->data, 3);
    EXPECT_EQ(tree.root->right->data, 1);
}

/// \brief Test the clear method of a binary tree
TEST(algorithm, binary_tree_clear) {
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
TEST(algorithm, binary_tree_insert_array) {
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
TEST(algorithm, binary_tree_insert_single_value) {
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

/// \brief Test the insertion of multiple values in a binary tree
TEST(algorithm, binary_tree_insert_multiple_values) {
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
TEST(algorithm, binary_tree_contains) {
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
TEST(algorithm, binary_tree_find) {
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
TEST(algorithm, binary_tree_is_empty) {
    bardrix::binary_tree<int> tree(int_predicate);

    EXPECT_TRUE(tree.is_empty());

    tree.build(1, 3, 4, 5, 6, 7, 8);

    EXPECT_FALSE(tree.is_empty());

    tree.clear();

    EXPECT_TRUE(tree.is_empty());
}

/// \brief Test the traverse method of a binary tree
TEST(algorithm, binary_tree_traverse) {
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
    EXPECT_EQ(values[0], 1);
    EXPECT_EQ(values[1], 3);
    EXPECT_EQ(values[2], 4);
    EXPECT_EQ(values[3], 5);
    EXPECT_EQ(values[4], 6);
    EXPECT_EQ(values[5], 7);
    EXPECT_EQ(values[6], 8);

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
    EXPECT_EQ(values[0], 2);
    EXPECT_EQ(values[1], 9);
    EXPECT_EQ(values[2], 10);
    EXPECT_EQ(values[3], 11);
    EXPECT_EQ(values[4], 12);
    EXPECT_EQ(values[5], 13);
    EXPECT_EQ(values[6], 14);
}

/// \brief Test the find_min method of a binary tree
TEST(algorithm, binary_tree_find_min) {
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
TEST(algorithm, binary_tree_find_max) {
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
TEST(algorithm, binary_tree_remove) {
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
    tree.remove(3);

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
    //          9      13       63     67
    //         / \       \     / \       \
    //        2  10      14   62 64      68
    tree.remove(11);
    tree.remove(65);

    EXPECT_EQ(tree.root->data, 24);
    EXPECT_EQ(tree.root->left->data, 12);
    EXPECT_EQ(tree.root->left->left->data, 9);
    EXPECT_EQ(tree.root->left->right->data, 13);
    EXPECT_EQ(tree.root->left->left->left->data, 2);
    EXPECT_EQ(tree.root->left->left->right->data, 10);
    EXPECT_EQ(tree.root->left->right->right->data, 14);
    EXPECT_EQ(tree.root->right->data, 66);
    EXPECT_EQ(tree.root->right->left->data, 63);
    EXPECT_EQ(tree.root->right->right->data, 67);
    EXPECT_EQ(tree.root->right->left->left->data, 62);
    EXPECT_EQ(tree.root->right->right->right->data, 68);
}