//
// Created by Bard on 15/03/2024.
//

#include <bardrix/vector3.h>

/// \brief Test the vector3 constructor with values
TEST(vector3, constructor_with_values) {
    bardrix::vector3 v(1, 2, 3);
    EXPECT_EQ(v.x, 1);
    EXPECT_EQ(v.y, 2);
    EXPECT_EQ(v.z, 3);
}

/// \brief Test the vector3 length/magnitude
TEST(vector3, length) {
    bardrix::vector3 v(1, 2, 3);
    EXPECT_EQ(v.length(), std::sqrt(14));
}

/// \brief Test the vector3 length/magnitude squared
TEST(vector3, length_squared) {
    bardrix::vector3 v(1, 2, 3);
    EXPECT_EQ(v.length_squared(), 14);
}

/// \brief Test the normalization of a vector3
TEST(vector3, normalized) {
    bardrix::vector3 v(1, 2, 3);
    bardrix::vector3 normalized = v.normalized();
    EXPECT_EQ(normalized, bardrix::vector3(1, 2, 3) / std::sqrt(14));
}

/// \brief Test the normalization of a vector3 with length 0
TEST(vector3, normalized_degenerate) {
    bardrix::vector3 v = bardrix::vector3(0, 0, 0);
    EXPECT_EQ(v.normalized(), v);
}

/// \brief Test the normalization of a vector3 with length 0
TEST(vector3, normalize) {
    bardrix::vector3 v(1, 2, 3);
    v.normalize();
    EXPECT_EQ(v, bardrix::vector3(1, 2, 3) / std::sqrt(14));
}

/// \brief Test the normalization of a vector3 with length 0
TEST(vector3, normalize_degenerate) {
    bardrix::vector3 v = bardrix::vector3(0, 0, 0);
    v.normalize();
    EXPECT_EQ(v, bardrix::vector3(0, 0, 0));
}

/// \brief Test the dot product of two vectors
TEST(vector3, dot) {
    bardrix::vector3 v1(1, 2, 3);
    bardrix::vector3 v2(4, 5, 6);
    EXPECT_EQ(v1.dot(v2), 32);
}

/// \brief Test the dot product of two vectors with one of them being 0
TEST(vector3, dot_zero) {
    bardrix::vector3 v1 = bardrix::vector3(0, 0, 0);
    bardrix::vector3 v2(4, 5, 6);
    bardrix::vector3 v3 = bardrix::vector3(0, 0, 0);

    EXPECT_EQ(v1.dot(v2), 0);
    EXPECT_EQ(v2.dot(v3), 0);
}

/// \brief Test the dot product of two vectors with one of them being negative
TEST(vector3, dot_negative) {
    bardrix::vector3 v1(1, 2, 3);
    bardrix::vector3 v2(-4, -5, -6);
    EXPECT_EQ(v1.dot(v2), -32);
}

/// \brief Test the cross product of two vectors
TEST(vector3, cross) {
    bardrix::vector3 v1(1, 2, 3);
    bardrix::vector3 v2(4, 5, 6);
    bardrix::vector3 cross = v1.cross(v2);
    EXPECT_EQ(cross.x, -3);
    EXPECT_EQ(cross.y, 6);
    EXPECT_EQ(cross.z, -3);
}

/// \brief Test the cross product of two vectors with one of them being 0
TEST(vector3, cross_degenerate) {
    bardrix::vector3 v1 = bardrix::vector3(0, 0, 0);
    bardrix::vector3 v2(4, 5, 6);
    bardrix::vector3 v3 = bardrix::vector3(0, 0, 0);
    bardrix::vector3 v4(7, 8, 9);

    bardrix::vector3 cross1 = v1.cross(v2);
    bardrix::vector3 cross2 = v3.cross(v4);

    EXPECT_EQ(cross1, v1);
    EXPECT_EQ(cross2, v3);
}

/// \brief Test the angle between two vectors
TEST(vector3, angle) {
    bardrix::vector3 v1(1, 2, 3);
    bardrix::vector3 v2(4, 5, 6);
    EXPECT_EQ(v1.angle(v2), 32 / (std::sqrt(14) * std::sqrt(77)));
}

/// \brief Test the angle between two vectors with one of them being 0
TEST(vector3, angle_zero) {
    bardrix::vector3 v1 = bardrix::vector3(0, 0, 0);
    bardrix::vector3 v2(4, 5, 6);
    EXPECT_EQ(v1.angle(v2), 1); // orthogonal
}


/// \brief Test the angle between two vectors with the other being 0
TEST(vector3, angle_zero_other) {
    bardrix::vector3 v1(1, 2, 3);
    bardrix::vector3 v2 = bardrix::vector3(0, 0, 0);
    EXPECT_EQ(v1.angle(v2), 1); // orthogonal
}

/// \brief Test the parallel angle between two vectors
TEST(vector3, angle_parallel) {
    bardrix::vector3 v1(1, 2, 3);
    bardrix::vector3 v2(2, 4, 6);
    EXPECT_EQ(v1.angle(v2), 1);
}

/// \brief Test the opposite angle between two vectors
TEST(vector3, angle_opposite) {
    bardrix::vector3 v1(1, 2, 3);
    bardrix::vector3 v2(-1, -2, -3);
    EXPECT_EQ(v1.angle(v2), -1);
}

/// \brief Test the orthogonal angle between two vectors
TEST(vector3, angle_orthogonal) {
    bardrix::vector3 v1(1, 0, 0);
    bardrix::vector3 v2(0, 1, 0);
    EXPECT_EQ(v1.angle(v2), 0);
}

/// \brief Test the << operator for vector3
TEST(vector3, print) {
    bardrix::vector3 v(1, 2, 3);
    std::stringstream ss;
    ss << v;
    EXPECT_EQ(ss.str(), "(1, 2, 3)");
}