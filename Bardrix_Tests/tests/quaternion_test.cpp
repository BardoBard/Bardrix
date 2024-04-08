//
// Created by Bard on 04/04/2024.
//

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
    bardrix::quaternion q3(-60, 12, 30, 24);
    EXPECT_EQ(q1 * q2, q3);
    EXPECT_EQ(q_zero * q1, q_zero);

    q1 = bardrix::quaternion(-53, 0, 34, 12);
    q2 = bardrix::quaternion(34, 17, 63, 23);
    q3 = bardrix::quaternion(-4220, -875, -1979, -1389);
    EXPECT_EQ(q1 * q2, q3);
}