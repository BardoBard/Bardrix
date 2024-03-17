//
// Created by Bard on 15/03/2024.
//

#include <bardrix/point3.h>

TEST(point3, constructor) {
    bardrix::point3 p;
    EXPECT_EQ(p.x, 0);
    EXPECT_EQ(p.y, 0);
    EXPECT_EQ(p.z, 0);
}

TEST(point3, constructor_with_values) {
    bardrix::point3 p(1, 2, 3);
    EXPECT_EQ(p.x, 1);
    EXPECT_EQ(p.y, 2);
    EXPECT_EQ(p.z, 3);
}

// Test the distance between two points
TEST(point3, distance) {
    bardrix::point3 p1(1, 2, 3);
    bardrix::point3 p2(4, 6, 8);
    bardrix::point3 p3_neg(-1, -2, -3);

    EXPECT_EQ(p1.distance(p2), std::sqrt(50));
    EXPECT_EQ(p1.distance(p3_neg), std::sqrt(56));
}

// Test the distance between two points with the same coordinates
TEST(point3, distance_degenerate) {
    bardrix::point3 p1;
    bardrix::point3 p2;
    EXPECT_EQ(p1.distance(p2), 0);
}

/// \brief Test the distance between two points squared
TEST(point3, distance_squared) {
    bardrix::point3 p1(1, 2, 3);
    bardrix::point3 p2(4, 6, 8);
    bardrix::point3 p3_neg(-1, -2, -3);

    EXPECT_EQ(p1.distance_squared(p2), 50);
    EXPECT_EQ(p1.distance_squared(p3_neg), 56);
}

/// \brief Test the distance between two points squared with the same coordinates
TEST(point3, distance_squared_degenerate) {
    bardrix::point3 p1;
    bardrix::point3 p2;
    EXPECT_EQ(p1.distance_squared(p2), 0);
}

/// \brief Test the midpoint between two points
TEST(point3, midpoint) {
    bardrix::point3 p1(1, 2, 3);
    bardrix::point3 p2(4, 6, 8);
    bardrix::point3 mid = p1.midpoint(p2);
    EXPECT_EQ(mid, bardrix::point3(2.5, 4, 5.5));
}

/// \brief Test the degenerate midpoint between two points
TEST(point3, midpoint_degenerate) {
    bardrix::point3 p1;
    bardrix::point3 p2;
    bardrix::point3 mid = p1.midpoint(p2);
    EXPECT_EQ(mid, bardrix::point3(0, 0, 0));
}

/// \brief Test the vector from one point to another
TEST(point3, vector_to) {
    bardrix::point3 p1(1, 2, 3);
    bardrix::point3 p2(4, 6, 8);
    bardrix::point3 p3_neg(-1, -2, -3);

    bardrix::vector3 v = p1.vector_to(p2);
    EXPECT_EQ(v, bardrix::vector3(3, 4, 5));

    v = p1.vector_to(p3_neg);
    EXPECT_EQ(v, bardrix::vector3(-2, -4, -6));
}

/// \brief Test the addition of a vector to a point
TEST(point3, operator_vector_plus) {
    bardrix::point3 p1(1, 2, 3);
    bardrix::vector3 v(4, 6, 8);
    bardrix::point3 p2 = p1 + v;
    EXPECT_EQ(p2, bardrix::point3(5, 8, 11));
}

/// \brief Test the addition of a vector to a point with negative values
TEST(point3, operator_plus_vector_negative) {
    bardrix::point3 p1(-1, -2, -3);
    bardrix::vector3 v(-4, -6, -8);
    bardrix::point3 p2 = p1 + v;
    EXPECT_EQ(p2, bardrix::point3(-5, -8, -11));
}

/// \brief Test the print method of a point3
TEST(point3, print) {
    bardrix::point3 p(1, 2, 3);
    std::stringstream ss;
    p.print(ss);
    EXPECT_EQ(ss.str(), "(1, 2, 3)");
}