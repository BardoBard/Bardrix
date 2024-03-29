//
// Created by Bardio on 29/03/2024.
//

#include <bardrix/color.h>

/// \brief Constructor tests
TEST(color, constructor) {
    std::cout << sizeof(void*) << std::endl;
    bardrix::color c1;
    EXPECT_EQ(c1.r(), 0);
    EXPECT_EQ(c1.g(), 0);
    EXPECT_EQ(c1.b(), 0);
    EXPECT_EQ(c1.a(), 0);
    EXPECT_EQ(c1.rgba(), 0);

    bardrix::color c2(255, 255, 255, 255);
    EXPECT_EQ(c2.r(), 255);
    EXPECT_EQ(c2.g(), 255);
    EXPECT_EQ(c2.b(), 255);
    EXPECT_EQ(c2.a(), 255);
    EXPECT_EQ(c2.rgba(), 0xFFFFFFFF);

    bardrix::color c3(0x00FF00FF);
    EXPECT_EQ(c3.r(), 255);
    EXPECT_EQ(c3.g(), 0);
    EXPECT_EQ(c3.b(), 255);
    EXPECT_EQ(c3.a(), 0);
    EXPECT_EQ(c3.rgba(), 0x00FF00FF);

    c1.r(255);
    c1.g(255);
    c1.b(255);
    c1.a(255);
    EXPECT_EQ(c1.r(), 255);
    EXPECT_EQ(c1.g(), 255);
    EXPECT_EQ(c1.b(), 255);
    EXPECT_EQ(c1.a(), 255);
    EXPECT_EQ(c1.rgba(), 0xFFFFFFFF);
}

/// \brief Test the color addition
TEST(color, operator_plus) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    bardrix::color c3 = c1 + c2;
    EXPECT_EQ(c3.rgba(), 0xFFFFFFFF);

    c3 = c1 + c1;
    EXPECT_EQ(c3.rgba(), 0xFFFFFFFF);

    c3 = c2 + c2;
    EXPECT_EQ(c3.rgba(), 0xFF6AFF08);

    c3 = c1 + c2 + c2;
    EXPECT_EQ(c3.rgba(), 0xFFFFFFFF);
}

/// \brief Test the color addition with a scalar
TEST(color, operator_plus_scalar) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    bardrix::color c3 = c1 + 4;
    EXPECT_EQ(c3.rgba(), 0xFFFFFFFF);

    c3 = c1 + 255;
    EXPECT_EQ(c3.rgba(), 0xFFFFFFFF);

    c3 = 255 + c1;
    EXPECT_EQ(c3.rgba(), 0xFFFFFFFF);

    c3 = c1 + 4 + c1;
    EXPECT_EQ(c3.rgba(), 0xFFFFFFFF);

    c3 = 5 + c2;
    EXPECT_EQ(c3.rgba(), 0xFF3AFF09);
}

/// \brief Test the color addition to itself with a scalar
TEST(color, operator_plus_equal) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 5, 53, 12);

    c1 += c2;
    EXPECT_EQ(c1.rgba(), 0xFFFFFFFF);

    c1 = bardrix::color(255, 255, 255, 255);
    c1 += c1;
    EXPECT_EQ(c1.rgba(), 0xFFFFFFFF);

    c2 += c2;
    EXPECT_EQ(c2.rgba(), 0x186A0A08);

    c2 = bardrix::color(4, 255, 53, 255);
    c2 += 4;
    EXPECT_EQ(c2.rgba(), 0xFF39FF08);
}

/// \brief Test the color subtraction
TEST(color, operator_minus) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);
    bardrix::color c3(52, 12, 52, 45);

    bardrix::color result = c1 - c2;
    EXPECT_EQ(result.rgba(), 0x00CA00FB);

    result = c1 - c1;
    EXPECT_EQ(result.rgba(), 0);

    result = c2 - c2;
    EXPECT_EQ(result.rgba(), 0);

    result = c1 - c2 - c2;
    EXPECT_EQ(result.rgba(), 0x009500F7);

    result = c3 - c2;
    EXPECT_EQ(result.rgba(), 0x00000030);
}

/// \brief Test the color subtraction with a scalar
TEST(color, operator_minus_scalar) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    bardrix::color result = c1 - 4;
    EXPECT_EQ(result.rgba(), 0xFBFBFBFB);

    result = c1 - 255;
    EXPECT_EQ(result.rgba(), 0);

    result = 255 - c1;
    EXPECT_EQ(result.rgba(), 0);

    result = c1 - 4 - c1;
    EXPECT_EQ(result.rgba(), 0);

    result = 5 - c2;
    EXPECT_EQ(result.rgba(), 1);
}

/// \brief Test the color subtraction to itself with a scalar
TEST(color, operator_minus_equal) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);
    bardrix::color c3(52, 12, 52, 45);

    c1 -= c2;
    EXPECT_EQ(c1.rgba(), 0x00CA00FB);

    c1 = bardrix::color(255, 255, 255, 255);
    c1 -= c1;
    EXPECT_EQ(c1.rgba(), 0);

    c2 -= c2;
    EXPECT_EQ(c2.rgba(), 0);

    c3 -= c2;
    EXPECT_EQ(c3.rgba(), 0x2D340C34);
}

/// \brief Test the color multiplication
TEST(color, operator_minus_equal_scalar) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    c1 -= 4;
    EXPECT_EQ(c1.rgba(), 0xFBFBFBFB);

    c1 = bardrix::color(255, 255, 255, 255);
    c1 -= 255;
    EXPECT_EQ(c1.rgba(), 0);

    c2 -= 4;
    EXPECT_EQ(c2.rgba(), 0xFB31FB00);
}

/// \brief Test the color multiplication
TEST(color, operator_multiply) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    bardrix::color result = c2 * 4;
    EXPECT_EQ(result.rgba(), 0xFFD4FF10);

    result = c1 * 1.5;
    EXPECT_EQ(result.rgba(), 0xFFFFFFFF);

    result = 0.2 * c1;
    EXPECT_EQ(result.rgba(), 0x33333333);

    result = 0.2 * c2;
    EXPECT_EQ(result.rgba(), 0x330A3300);
}

/// \brief Test the color multiplication to itself
TEST(color, operator_multiply_equal) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    c1 *= 4;
    EXPECT_EQ(c1.rgba(), 0xFFFFFFFF);

    c2 *= 1.5;
    EXPECT_EQ(c2.rgba(), 0xFF4FFF06);

    c2 = bardrix::color(4, 255, 53, 255);
    c2 *= 0.2;
    EXPECT_EQ(c2.rgba(), 0x330A3300);
}

/// \brief Test the color multiplication by zero and negative values
TEST(color, operator_multiply_degenerate) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    bardrix::color result = c1 * 0;
    EXPECT_EQ(result.rgba(), 0);

    result = 0 * c1;
    EXPECT_EQ(result.rgba(), 0);

    result = c2 * -5;
    EXPECT_EQ(result.rgba(), 0);

    result = c2 * -0.1;
    EXPECT_EQ(result.rgba(), 0);

    result = { 2, 4, 5, 6 };
    result *= 0;
    EXPECT_EQ(result.rgba(), 0);
}

/// \brief Test the color division
TEST(color, operator_divide) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    bardrix::color result = c2 / 4;
    EXPECT_EQ(result.rgba(), 0x3F0D3F01);

    result = c1 / 1.5;
    EXPECT_EQ(result.rgba(), 0xAAAAAAAA);

    result = 0.2 / c1;
    EXPECT_EQ(result.rgba(), 0);

    result = c2 / 0.2;
    EXPECT_EQ(result.rgba(), 0xFFFFFF14);
}

/// \brief Test the color division to itself
TEST(color, operator_divide_equal) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    c1 /= 4;
    EXPECT_EQ(c1.rgba(), 0x3F3F3F3F);

    c2 /= 1.5;
    EXPECT_EQ(c2.rgba(), 0xAA23AA02);

    c2 = bardrix::color(4, 255, 53, 255);
    c2 /= 0.2;
    EXPECT_EQ(c2.rgba(), 0xFFFFFF14);
}

/// \brief Test the color division by zero and negative values
TEST(color, operator_divide_degenerate) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(0, 0, 0, 0);

    EXPECT_THROW(c1 / 0, std::invalid_argument);
    EXPECT_THROW(c2 / 0, std::invalid_argument);
    EXPECT_THROW(c1 / -0.2, std::invalid_argument);
    EXPECT_THROW(c2 / -1, std::invalid_argument);

    EXPECT_THROW(c1 /= 0, std::invalid_argument);
    EXPECT_THROW(c2 /= 0, std::invalid_argument);
    EXPECT_THROW(c1 /= -0.2, std::invalid_argument);
    EXPECT_THROW(c2 /= -1, std::invalid_argument);

    EXPECT_NO_THROW(123 / c1);
    EXPECT_THROW(123 / c2, std::invalid_argument);
    EXPECT_THROW(-0.2 / c1, std::invalid_argument);
    EXPECT_THROW(-1 / c2, std::invalid_argument);
}

/// \brief Tests the color equality
TEST(color, operator_equal) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);
    bardrix::color c3(4, 255, 53, 255);

    EXPECT_TRUE(c1 == c1);
    EXPECT_TRUE(c2 == c2);
    EXPECT_TRUE(c3 == c3);

    EXPECT_TRUE(c2 == c3);
    EXPECT_TRUE(c3 == c2);

    EXPECT_FALSE(c1 == c3);
    EXPECT_FALSE(c1 == c2);
}

/// \brief Tests the color inequality
TEST(color, operator_not_equal) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);
    bardrix::color c3(4, 255, 53, 255);

    EXPECT_FALSE(c1 != c1);
    EXPECT_FALSE(c2 != c2);
    EXPECT_FALSE(c3 != c3);

    EXPECT_FALSE(c2 != c3);
    EXPECT_FALSE(c3 != c2);

    EXPECT_TRUE(c1 != c2);
    EXPECT_TRUE(c1 != c3);
}

/// \brief Test the color print
TEST(color, print) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    std::stringstream ss;
    c1.print(ss);
    EXPECT_EQ(ss.str(), "(255, 255, 255, 255)");

    ss.str("");
    c2.print(ss);
    EXPECT_EQ(ss.str(), "(4, 255, 53, 255)");
}

/// \brief Test the color stream operator
TEST(color, stream_operator) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    std::stringstream ss;
    ss << c1;
    EXPECT_EQ(ss.str(), "(255, 255, 255, 255)");

    ss.str("");
    ss << c2;
    EXPECT_EQ(ss.str(), "(4, 255, 53, 255)");
}