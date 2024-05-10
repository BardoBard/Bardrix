//
// Created by Bard on 04/04/2024.
//

#include <bardrix/vector3.h>
#include <bardrix/point3.h>
#include <bardrix/quaternion.h>

/// \brief Test the quaternion constructor
TEST(quaternion, constructor) {
    bardrix::quaternion q;
    EXPECT_EQ(q, bardrix::quaternion(0, 0, 0, 0));

    q = bardrix::quaternion(1, 2, 3, 4);
    EXPECT_EQ(q, bardrix::quaternion(1, 2, 3, 4));
}

/// \brief Test the identity quaternion
TEST(quaternion, identity) {
    bardrix::quaternion q = bardrix::quaternion::identity();
    EXPECT_EQ(q, bardrix::quaternion(0, 0, 0, 1));
}

/// \brief Test the quaternion conjugation
TEST(quaternion, conjugate) {
    bardrix::quaternion q(1, 2, 3, 4);

    q.conjugate();
    EXPECT_EQ(q, bardrix::quaternion(-1, -2, -3, 4));
}

/// \brief Test the quaternion conjugation
TEST(quaternion, conjugated) {
    bardrix::quaternion q(1, 2, 3, 4);
    bardrix::quaternion q2(0, -2, 2, -4);

    EXPECT_EQ(q.conjugated(), bardrix::quaternion(-1, -2, -3, 4));
    EXPECT_EQ(q2.conjugated(), bardrix::quaternion(0, 2, -2, -4));
}

/// \brief Test the quaternion reciprocal
TEST(quaternion, reciprocal) {
    bardrix::quaternion q(1, 2, 3, 4);
    q.reciprocal();
    EXPECT_EQ(q, bardrix::quaternion(-0.0333, -0.0666, -0.1, 0.1333));
}

/// \brief Test the quaternion reciprocal
TEST(quaternion, reciprocated) {
    bardrix::quaternion q(1, 2, 3, 4);
    bardrix::quaternion q2(-0.033333, -0.066666, -0.1, 0.133333);

    EXPECT_EQ(q.reciprocated(), bardrix::quaternion(-0.0333, -0.0666, -0.1, 0.1333));
    EXPECT_EQ(q2.reciprocated(), bardrix::quaternion(1, 2, 3, 4));
}

/// \brief Test the quaternion reciprocal with zero length
TEST(quaternion, reciprocal_zero) {
    bardrix::quaternion q(0, 0, 0, 0);
    q.reciprocal();
    EXPECT_EQ(q, bardrix::quaternion(0, 0, 0, 0));
}

/// \brief Test the length of a quaternion
TEST(quaternion, length) {
    bardrix::quaternion q(1, 2, 3, 4);
    EXPECT_NEAR(q.length(), 5.477225575051661, 0.0001);
}

/// \brief Test the length of a quaternion with negative values and zero
TEST(quaternion, length_degenerate) {
    bardrix::quaternion q(0, 0, 0, 0);
    bardrix::quaternion q2(-1, -2, -3, -4);
    EXPECT_NEAR(q.length(), 0, 0.0001);
    EXPECT_NEAR(q2.length(), 5.477225575051661, 0.0001);
}

/// \brief Test the normalization of a quaternion
TEST(quaternion, normalize) {
    bardrix::quaternion q(1, 2, 3, 4);
    bardrix::quaternion q2(0.182574, 0.365148, 0.547723, 0.730297);
    bardrix::quaternion q3(-1, -2, -3, -4);

    q.normalize();
    EXPECT_EQ(q, bardrix::quaternion(0.182574, 0.365148, 0.547723, 0.730297));

    q2.normalize();
    EXPECT_EQ(q2, bardrix::quaternion(0.182574, 0.365148, 0.547723, 0.730297));

    q3.normalize();
    EXPECT_EQ(q3, bardrix::quaternion(-0.182574, -0.365148, -0.547723, -0.730297));
}

/// \brief Test the normalization of a quaternion
TEST(quaternion, normalized) {
    bardrix::quaternion q(1, 2, 3, 4);
    bardrix::quaternion q2(0.182574, 0.365148, 0.547723, 0.730297);
    bardrix::quaternion q3(-1, -2, -3, -4);

    EXPECT_EQ(q.normalized(), bardrix::quaternion(0.182574, 0.365148, 0.547723, 0.730297));
    EXPECT_EQ(q2.normalized(), bardrix::quaternion(0.182574, 0.365148, 0.547723, 0.730297));
    EXPECT_EQ(q3.normalized(), bardrix::quaternion(-0.182574, -0.365148, -0.547723, -0.730297));
}

/// \brief Test the normalization of a quaternion with zero length
TEST(quaternion, normalize_zero) {
    bardrix::quaternion q(0, 0, 0, 0);
    q.normalize();
    EXPECT_EQ(q, bardrix::quaternion(0, 0, 0, 0));
}

/// \brief Test the normalization of a quaternion with zero length
TEST(quaternion, normalized_degenerate) {
    bardrix::quaternion q(0, 0, 0, 0);
    EXPECT_EQ(q.normalized(), bardrix::quaternion(0, 0, 0, 0));

    bardrix::quaternion q2(-1, -2, -3, -4);
    EXPECT_EQ(q2.normalized(), bardrix::quaternion(-0.182574, -0.365148, -0.547723, -0.730297));

    q.normalize();
    EXPECT_EQ(q, bardrix::quaternion(0, 0, 0, 0));

    q2.normalize();
    EXPECT_EQ(q2, bardrix::quaternion(-0.182574, -0.365148, -0.547723, -0.730297));
}

/// \brief Test the dot product of two quaternions
TEST(quaternion, multiply) {
    bardrix::quaternion q_zero(0, 0, 0, 0);
    bardrix::quaternion q1(1, 2, 3, 4);
    bardrix::quaternion q2(5, 6, 7, 8);
    bardrix::quaternion q3(24, 48, 48, -6);
    EXPECT_EQ(q1 * q2, q3);
    EXPECT_EQ(q_zero * q1, q_zero);

    q1 = bardrix::quaternion(-53, 0, 34, 12);
    q2 = bardrix::quaternion(34, 17, 63, 23);
    q3 = bardrix::quaternion(-1389, 4699, 637, -64);
    EXPECT_EQ(q1 * q2, q3);
}

/// \brief Test the rotation of a quaternion
TEST(quaternion, rotation_theta_test) {
    bardrix::vector3 rotation_vector = {1, 2, 3};
    bardrix::vector3 vector = {4, 5, 6};
    bardrix::point3 point = {4, 5, 6};

    double theta = 90.0;
    bardrix::vector3 result = bardrix::quaternion::rotate_degrees(vector, rotation_vector, theta);
    bardrix::point3 result_point = bardrix::quaternion::rotate_degrees(point, rotation_vector, theta);
    ASSERT_EQ(result, bardrix::vector3(3.0875, 2.9678, 7.6589));
    ASSERT_EQ(result_point, bardrix::point3(3.0875, 2.9678, 7.6589));

    theta = 180.0;
    result = bardrix::quaternion::rotate_degrees(vector, rotation_vector, theta);
    result_point = bardrix::quaternion::rotate_degrees(point, rotation_vector, theta);
    ASSERT_EQ(result, bardrix::vector3(0.5714, 4.1428, 7.7143));
    ASSERT_EQ(result_point, bardrix::point3(0.5714, 4.1428, 7.7143));

    theta = 270.0;
    result = bardrix::quaternion::rotate_degrees(vector, rotation_vector, theta);
    result_point = bardrix::quaternion::rotate_degrees(point, rotation_vector, theta);
    ASSERT_EQ(result, bardrix::vector3(1.4839, 6.175, 6.0553));
    ASSERT_EQ(result_point, bardrix::point3(1.4839, 6.175, 6.0553));

    theta = 360.0;
    result = bardrix::quaternion::rotate_degrees(vector, rotation_vector, theta);
    result_point = bardrix::quaternion::rotate_degrees(point, rotation_vector, theta);
    ASSERT_EQ(result, vector);
    ASSERT_EQ(result_point, point);
}

/// \brief Test the rotation of a quaternion with degenerate cases
TEST(quaternion, rotation_degeneratie_position){
    bardrix::vector3 rotation_vector = {1, 2, 3};
    bardrix::vector3 rotation_vector_neg = {-11, 31, 0};
    bardrix::point3 point_zero = { 0, 0, 0};
    bardrix::point3 point_neg = {-24,34,-12};
    double theta = 90.0;

    bardrix::point3 result = bardrix::quaternion::rotate_degrees(point_zero, rotation_vector, theta);
    ASSERT_EQ(result, bardrix::point3(0, 0, 0));

    result = bardrix::quaternion::rotate_degrees(point_neg, rotation_vector, theta);
    ASSERT_EQ(result, bardrix::point3(34.2463, 17.1785, -20.2011));

    result = bardrix::quaternion::rotate_degrees(point_neg, rotation_vector_neg, theta);
    ASSERT_EQ(result, bardrix::point3(-2.09013, 41.7745, -11.2483));
}

/// \brief Test the rotation of a quaternion with zero theta
TEST(quaternion, rotation_vector_zero_theta_test) {
    bardrix::vector3 rotation_vector = bardrix::vector3(1, 2, 3);
    bardrix::vector3 vector = bardrix::vector3(4, 5, 6);
    double theta = 0;

    bardrix::vector3 result = bardrix::quaternion::rotate_degrees(vector, rotation_vector, theta);

    ASSERT_EQ(result, vector);
}

/// \brief Test the rotation of a quaternion with negative theta
TEST(quaternion, rotation_vector_negative_theta_test) {
    bardrix::vector3 rotation_vector = {1, 2, 3};
    bardrix::vector3 vector = {4, 5, 6};
    double theta = -90.0;

    bardrix::vector3 result = bardrix::quaternion::rotate_degrees(vector, rotation_vector, theta);

    ASSERT_EQ(result, bardrix::vector3(1.4839, 6.175, 6.05536));
}

/// \brief Test degenerate cases of the rotation of a quaternion
TEST(quaternion, rotation_degenerate_test) {
    bardrix::vector3 rotation_vector = {0, 0, 0};
    bardrix::vector3 vector = {4, 5, 6};
    double theta = 90.0;

    bardrix::vector3 result = bardrix::quaternion::rotate_degrees(vector, rotation_vector, theta);

    ASSERT_EQ(result, vector);
}

/// \brief Test degenerate cases of the rotation of a quaternion
TEST(quaternion, rotation_degenerate_test2) {
    bardrix::vector3 rotation_vector = {1, 2, 3};
    bardrix::vector3 vector = {0, 0, 0};
    double theta = 90.0;

    bardrix::vector3 result = bardrix::quaternion::rotate_degrees(vector, rotation_vector, theta);

    ASSERT_EQ(result, vector);
}

/// \brief Test the mirror of a quaternion
TEST(quaternion, mirror) {
    bardrix::vector3 rotation_vector = {1, 2, 3};
    bardrix::vector3 vector = {4, 5, 6};

    bardrix::vector3 result = bardrix::quaternion::mirror(vector, rotation_vector);
    ASSERT_EQ(result, bardrix::vector3(0.5714, 4.1428, 7.7143));
}

/// \brief Test the mirror of a quaternion
TEST(quaternion, mirror2) {
    bardrix::vector3 rotation_vector = {1, 0,0};
    bardrix::vector3 vector = {1, 2, 3};

    bardrix::vector3 result = bardrix::quaternion::mirror(vector, rotation_vector);
    ASSERT_EQ(result, bardrix::vector3(1, -2, -3));
}

/// \brief Test the mirror of a quaternion with degenerate cases
TEST(quaternion, mirror_degenerate) {
    bardrix::vector3 rotation_vector = {1, 2, 3};
    bardrix::vector3 vector = {0, 0, 0};

    bardrix::vector3 result = bardrix::quaternion::mirror(vector, rotation_vector);
    ASSERT_EQ(result, 0);
}

/// \brief Test the mirror of a quaternion with degenerate cases
TEST(quaternion, mirror_degenerate2) {
    bardrix::vector3 rotation_vector = {0, 0, 0};
    bardrix::vector3 vector = {4, 5, 6};

    bardrix::vector3 result = bardrix::quaternion::mirror(vector, rotation_vector);
    ASSERT_EQ(result, vector);

    rotation_vector = {-23,52,0};
    result = bardrix::quaternion::mirror(vector, rotation_vector);
    ASSERT_EQ(result, bardrix::vector3(-6.3903, 0.40426, -6));
}

/// \brief Test the print method of a quaternion
TEST(quaternion, print) {
    bardrix::quaternion q(1, 2, 3, 4);
    std::stringstream ss;
    q.print(ss);
    EXPECT_EQ(ss.str(), "quaternion(1i, 2j, 3k, 4)");
}
