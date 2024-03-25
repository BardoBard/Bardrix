//
// Created by Bardio on 17/03/2024.
//

#include <bardrix/ray.h>

/// \brief Default constructor for ray, (0,0,0) direction (0,0,1), length 1
TEST(ray, constructor) {
    bardrix::ray r = bardrix::ray({0, 0, 1});
    EXPECT_EQ(r.position, bardrix::point3());
    EXPECT_EQ(r.get_direction(), bardrix::vector3(0, 0, 1));
    EXPECT_DOUBLE_EQ(r.get_direction().length(), 1);
    EXPECT_EQ(r.get_length(), 1);
}

/// \brief Constructor for ray, initializes position and direction
TEST(ray, constructor_with_values) {
    bardrix::ray r(bardrix::point3(1, 2, 3), bardrix::vector3(4, 5, 6));
    EXPECT_EQ(r.position, bardrix::point3(1, 2, 3));
    EXPECT_EQ(r.get_direction(), bardrix::vector3(4, 5, 6).normalized());
    EXPECT_DOUBLE_EQ(r.get_direction().length(), 1);
    EXPECT_EQ(r.get_length(), bardrix::vector3(4, 5, 6).length());
}

/// \brief Constructor for ray, initializes position, direction and length
TEST(ray, constructor_with_values_and_length) {
    bardrix::ray r(bardrix::point3(1, 2, 3), bardrix::vector3(4, 5, 6), 7);
    EXPECT_EQ(r.position, bardrix::point3(1, 2, 3));
    EXPECT_EQ(r.get_direction(), bardrix::vector3(4, 5, 6).normalized());
    EXPECT_DOUBLE_EQ(r.get_direction().length(), 1);
    EXPECT_EQ(r.get_length(), 7);
}

/// \brief Constructor degenerate with zero direction
TEST(ray, constructor_degenerate) {
    EXPECT_NO_THROW(bardrix::ray({0, 0, 0}));
    EXPECT_NO_THROW(bardrix::ray(bardrix::point3(1, 2, 3), bardrix::vector3(0, 0, 0), 29));
    EXPECT_NO_THROW(bardrix::ray(bardrix::point3(1, 2, 3), bardrix::vector3(0, 0, 0)));
}

/// \brief Test the point at a distance from the position
TEST(ray, point_at) {
    bardrix::ray r(bardrix::point3(1, 2, 3), bardrix::vector3(0, 0, 1), 7);
    EXPECT_EQ(r.point_at(0), bardrix::point3(1, 2, 3));
    EXPECT_EQ(r.point_at(7), bardrix::point3(1, 2, 10));
    EXPECT_EQ(r.point_at(14), bardrix::point3(1, 2, 17));
}

/// \brief Test the point at a distance from the position with a negative distance
TEST(ray, point_at_negative) {
    bardrix::ray r(bardrix::point3(1, 2, 3), bardrix::vector3(0, 0, 1), 7);
    EXPECT_EQ(r.point_at(-7), bardrix::point3(1, 2, 3));
    EXPECT_EQ(r.point_at(-14), bardrix::point3(1, 2, 3));
    EXPECT_EQ(r.point_at(-0), bardrix::point3(1, 2, 3));
    EXPECT_EQ(r.point_at(0), bardrix::point3(1, 2, 3));
}

/// \brief Test the point at the end of the ray
TEST(ray, end) {
    bardrix::ray r(bardrix::point3(1, 2, 3), bardrix::vector3(-2, -0, 0), 5);
    EXPECT_EQ(r.get_end(), bardrix::point3(-4, 2, 3));
}

/// \brief Test the print method
TEST(ray, print) {
    bardrix::ray r(bardrix::point3(1, 2, 3), bardrix::vector3(0, 0, 1), 7);
    std::stringstream ss;
    r.print(ss);
    EXPECT_EQ(ss.str(), "Position: (1, 2, 3), Direction: (0, 0, 1), Length: 7");
}

/// \brief Test the set direction method
TEST(ray, set_direction) {
    bardrix::ray r = bardrix::ray({0, 0, 1});
    r.set_direction(bardrix::vector3(-4, 5, -6));
    EXPECT_EQ(r.get_direction(), bardrix::vector3(-4, 5, -6).normalized());
    EXPECT_DOUBLE_EQ(r.get_direction().length(), 1);
}

/// \brief Test the set direction method with a zero vector
TEST(ray, set_direction_zero) {
    bardrix::ray r = bardrix::ray(bardrix::point3(1, 2, 3), bardrix::vector3(4, 5, 6));
    EXPECT_NO_THROW(r.set_direction(bardrix::vector3(0, 0, 0)));

    EXPECT_EQ(r.get_direction(), bardrix::vector3(0, 0, 0));
}

/// \brief Test the set length method
TEST(ray, set_length) {

    bardrix::ray r = bardrix::ray({0, 0, 1});
    r.set_length(7);
    EXPECT_EQ(r.get_length(), 7);
}

/// \brief Test the set length method with a negative value
TEST(ray, set_length_negative) {
    bardrix::ray r = bardrix::ray({0, 0, 1});
    r.set_length(-7);
    EXPECT_EQ(r.get_length(), 0);
}

/// \brief Test the equality operator
TEST(ray, operator_stream) {
    bardrix::ray r = bardrix::ray({0, 0, 1});
    std::stringstream ss;
    ss << r;
    EXPECT_EQ(ss.str(), "Position: (0, 0, 0), Direction: (0, 0, 1), Length: 1");
}