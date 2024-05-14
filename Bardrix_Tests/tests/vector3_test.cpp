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
    EXPECT_EQ(v.normalize(), bardrix::vector3(1, 2, 3) / std::sqrt(14));
    EXPECT_EQ(v, bardrix::vector3(1, 2, 3) / std::sqrt(14));
}

/// \brief Test the normalization of a vector3 with length 0
TEST(vector3, normalize_degenerate) {
    bardrix::vector3 v = bardrix::vector3(0, 0, 0);
    EXPECT_EQ(v.normalize(), bardrix::vector3(0, 0, 0));
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

/// \brief Test the reflection of a vector
TEST(vector3, reflect) {
    bardrix::vector3 v1(1, 2, 3);
    bardrix::vector3 normal(0, 0, 1);

    std::optional<bardrix::vector3> result = v1.reflect(normal);
    EXPECT_TRUE(result.has_value());
    ASSERT_TRUE(bardrix::nearly_equal(result->length_squared(), 1));
    EXPECT_EQ(result.value(), bardrix::vector3(1, 2, -3).normalized());
}

/// \brief Test the reflection of a vector with the vector behind the normal and other degenerate cases
TEST(vector3, reflect_degenerate) {
    bardrix::vector3 v1(1, 2, 3);
    bardrix::vector3 normal(0, 0, -1);

    std::optional<bardrix::vector3> reflected = v1.reflect(normal);
    EXPECT_FALSE(reflected.has_value());

    bardrix::vector3 v_zero(0, 0, 0);
    bardrix::vector3 normal_zero(0, 0, 0);

    std::optional<bardrix::vector3> reflected_zero = v_zero.reflect({ 0, 0, 1 });
    std::optional<bardrix::vector3> reflected_normal_zero = v1.reflect(normal_zero);

    EXPECT_FALSE(reflected_zero.has_value());
    EXPECT_FALSE(reflected_normal_zero.has_value());
}

/// \brief Refraction of a vector
TEST(vector3, refract) {
    bardrix::vector3 v1(1, 2, 3);
    bardrix::vector3 normal(0, 0, 1);

    double refractive_index1 = 1;     // vacuum
    double refractive_index2 = 2.419; // diamond

    std::optional<bardrix::vector3> result = v1.refract(normal, refractive_index1, refractive_index2);
    EXPECT_TRUE(result.has_value());
    ASSERT_TRUE(bardrix::nearly_equal(result->length_squared(), 1));
    EXPECT_EQ(result.value(), bardrix::vector3(0.1105, 0.2209, -0.969));
}

/// \brief Refraction of a vector
TEST(vector3, refract2) {
    const bardrix::vector3 v1 = { 0.707107, -0.707107, 0.0 }; // already normalized
    const bardrix::vector3 normal = { 0.0, 1.0, 0.0 };
    const double refractive_ratio = 0.9;

    const auto result = v1.refract(normal, refractive_ratio);

    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(bardrix::nearly_equal(result->length_squared(), 1));
    ASSERT_EQ(bardrix::vector3(0.636396, -0.771363, 0.0), *result);
}

/// \brief Refraction of a vector
TEST(vector3, refract3) {
    const bardrix::vector3 v1 = { 1.191752, 1, 0 }; // 50 degrees
    const bardrix::vector3 normal = { 0.0, 1.0, 0.0 };
    const double refractive_ratio_2 = 1.2;

    // calculate refraction
    const auto result = v1.refract(normal, refractive_ratio_2);
    std::cout << *result << std::endl;

    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(bardrix::nearly_equal(result->length_squared(), 1));
    ASSERT_EQ(bardrix::vector3(0.919253, -0.393668, 0), *result);

    // calculate angle in degrees
    const double angle = bardrix::radians_to_degrees(std::acos(result->angle(normal)));
    ASSERT_TRUE(bardrix::nearly_equal(66.817, 180 - angle));
}

/// \biref Degenerate cases for refraction
TEST(vector3, refract_degenerate) {
    bardrix::vector3 v1(1, 2, 3);
    bardrix::vector3 normal(0, 0, 1);

    // approaching total internal reflection
    EXPECT_FALSE(v1.refract(normal, 1.67333, 1).has_value());
    EXPECT_TRUE(v1.refract(normal, 1.67332, 1).has_value());

    // approaching total internal reflection
    EXPECT_FALSE(v1.refract(normal, 1.67333).has_value());
    EXPECT_TRUE(v1.refract(normal, 1.67332).has_value());

    // large values for medium 2
    EXPECT_TRUE(v1.refract(normal, 1, 241).has_value());
    EXPECT_TRUE(v1.refract(normal, 1, 1000).has_value());

    // negative
    EXPECT_FALSE(v1.refract(normal, -1, 1).has_value());
    EXPECT_FALSE(v1.refract(normal, 1, -1).has_value());
    EXPECT_FALSE(v1.refract(normal, -1).has_value());
    EXPECT_TRUE(v1.refract(normal, 1).has_value());

    // zero
    EXPECT_FALSE(v1.refract(normal, 0, 2).has_value());
    EXPECT_FALSE(v1.refract(normal, 2, 0).has_value());

    EXPECT_FALSE(v1.refract(normal, 0).has_value());
    EXPECT_TRUE(v1.refract(normal, 0.1).has_value());

    bardrix::vector3 v_zero(0, 0, 0);
    bardrix::vector3 normal_zero(0, 0, 0);

    EXPECT_FALSE(v_zero.refract({ 0, 0, 1 }, 1, 1).has_value()); // zero vector
    EXPECT_FALSE(v1.refract(normal_zero, 1, 1).has_value());     // zero normal
}

/// \brief Test the << operator for vector3
TEST(vector3, print) {
    bardrix::vector3 v(1, 2, 3);
    std::stringstream ss;
    ss << v;
    EXPECT_EQ(ss.str(), "(1, 2, 3)");
}