//
// Created by Bardio on 29/03/2024.
//

#include <bardrix/color.h>

/// \brief Constructor tests
TEST(color, constructor) {
    bardrix::color c1;
    EXPECT_EQ(c1.r(), 0);
    EXPECT_EQ(c1.g(), 0);
    EXPECT_EQ(c1.b(), 0);
    EXPECT_EQ(c1.a(), 0);
    EXPECT_EQ(c1.abgr(), 0);

    bardrix::color c2(255, 255, 255, 255);
    EXPECT_EQ(c2.r(), 255);
    EXPECT_EQ(c2.g(), 255);
    EXPECT_EQ(c2.b(), 255);
    EXPECT_EQ(c2.a(), 255);
    EXPECT_EQ(c2.abgr(), 0xFFFFFFFF);

    bardrix::color c3(0x00FF00FF);
    EXPECT_EQ(c3.r(), 0);
    EXPECT_EQ(c3.g(), 255);
    EXPECT_EQ(c3.b(), 0);
    EXPECT_EQ(c3.a(), 255);
    EXPECT_EQ(c3.abgr(), 0xFF00FF00);

    c1.r(255);
    c1.g(255);
    c1.b(255);
    c1.a(255);
    EXPECT_EQ(c1.r(), 255);
    EXPECT_EQ(c1.g(), 255);
    EXPECT_EQ(c1.b(), 255);
    EXPECT_EQ(c1.a(), 255);
    EXPECT_EQ(c1.abgr(), 0xFFFFFFFF);
}

/// \brief Test the inverse color
TEST(color, invert) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    EXPECT_EQ((~c1).abgr(), 0xFF000000);
    EXPECT_EQ(c1.inverted().abgr(), 0xFF000000);
    EXPECT_EQ(c1.invert().abgr(), 0xFF000000);

    EXPECT_EQ((~c2).abgr(), 0xFFCA00FB);
    EXPECT_EQ(c2.inverted().abgr(), 0xFFCA00FB);
    EXPECT_EQ(c2.invert().abgr(), 0xFFCA00FB);
}

/// \brief Test grayscale of colors
TEST(color, grayscale) {
    EXPECT_EQ(bardrix::color(255, 0, 0, 255).grayscale().abgr(), 0xFF4C4C4C); // Red
    EXPECT_EQ(bardrix::color(0, 255, 0, 255).grayscale().abgr(), 0xFF969696); // Green
    EXPECT_EQ(bardrix::color(0, 0, 255, 255).grayscale().abgr(), 0xFF1D1D1D); // Blue
    EXPECT_EQ(bardrix::color(255, 255, 255, 255).grayscale().abgr(), 0xFFFFFFFF); // White
    EXPECT_EQ(bardrix::color(0, 0, 0, 255).grayscale().abgr(), 0xFF000000); // Black
    EXPECT_EQ(bardrix::color(255, 255, 0, 255).grayscale().abgr(), 0xFFE2E2E2); // Yellow
    EXPECT_EQ(bardrix::color(255, 0, 255, 255).grayscale().abgr(), 0xFF696969); // Magenta (nice)
    EXPECT_EQ(bardrix::color(0, 255, 255, 255).grayscale().abgr(), 0xFFB3B3B3); // Cyan
    EXPECT_EQ(bardrix::color(128, 0, 0, 255).grayscale().abgr(), 0xFF262626); // Maroon
    EXPECT_EQ(bardrix::color(34, 12, 72, 255).grayscale().abgr(), 0xFF191919); // Random
}

/// \brief Test grayscale of colors
TEST(color, grayscaled) {
    EXPECT_EQ(bardrix::color(255, 0, 0, 255).grayscaled().abgr(), 0xFF4C4C4C); // Red
    EXPECT_EQ(bardrix::color(0, 255, 0, 255).grayscaled().abgr(), 0xFF969696); // Green
    EXPECT_EQ(bardrix::color(0, 0, 255, 255).grayscaled().abgr(), 0xFF1D1D1D); // Blue
    EXPECT_EQ(bardrix::color(255, 255, 255, 255).grayscaled().abgr(), 0xFFFFFFFF); // White
    EXPECT_EQ(bardrix::color(0, 0, 0, 255).grayscaled().abgr(), 0xFF000000); // Black
    EXPECT_EQ(bardrix::color(255, 255, 0, 255).grayscaled().abgr(), 0xFFE2E2E2); // Yellow
    EXPECT_EQ(bardrix::color(255, 0, 255, 255).grayscaled().abgr(), 0xFF696969); // Magenta (nice)
    EXPECT_EQ(bardrix::color(0, 255, 255, 255).grayscaled().abgr(), 0xFFB3B3B3); // Cyan
    EXPECT_EQ(bardrix::color(128, 0, 0, 255).grayscaled().abgr(), 0xFF262626); // Maroon
    EXPECT_EQ(bardrix::color(34, 12, 72, 255).grayscaled().abgr(), 0xFF191919); // Random
}

/// \brief Test blending of colors
TEST(color, blend) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);
    bardrix::color c3(4, 34, 53, 255);

    c1.blend(c2);
    EXPECT_EQ(c1.rgba(), 0x81FF9AFF);

    c1 = bardrix::color(255, 255, 255, 255);
    c2.blend(c1);
    EXPECT_EQ(c2.rgba(), 0x81FF9AFF);

    c2 = bardrix::color(4, 255, 53, 255);
    c2.blend(c3);
    EXPECT_EQ(c2.rgba(), 0x049035FF);

    c2 = bardrix::color(4, 255, 53, 255);
    c3.blend(c2);
    EXPECT_EQ(c3.rgba(), 0x049035FF);

    c3 = bardrix::color(4, 34, 53, 255);
    c1.blend(c3);
    EXPECT_EQ(c1.rgba(), 0x81909AFF);

    c1 = bardrix::color(255, 255, 255, 255);
    c3.blend(c1);
    EXPECT_EQ(c3.rgba(), 0x81909AFF);
}

/// \brief Test blending of colors
TEST(color, blended) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);
    bardrix::color c3(4, 34, 53, 255);

    EXPECT_EQ(c1.blended(c2).rgba(), 0x81FF9AFF);
    EXPECT_EQ(c2.blended(c1).rgba(), 0x81FF9AFF);

    EXPECT_EQ(c2.blended(c3).rgba(), 0x049035FF);
    EXPECT_EQ(c3.blended(c2).rgba(), 0x049035FF);

    EXPECT_EQ(c1.blended(c3).rgba(), 0x81909AFF);
    EXPECT_EQ(c3.blended(c1).rgba(), 0x81909AFF);
}

/// \brief Test the get rgba method
TEST(color, rgba) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    EXPECT_EQ(c1.rgba(), 0xFFFFFFFF);
    EXPECT_EQ(c2.rgba(), 0x04FF35FF);
}

/// \brief Test the get abgr method
TEST(color, abgr) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    EXPECT_EQ(c1.abgr(), 0xFFFFFFFF);
    EXPECT_EQ(c2.abgr(), 0xFF35FF04);
}

/// \brief Test the get argb method
TEST(color, argb) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    EXPECT_EQ(c1.argb(), 0xFFFFFFFF);
    EXPECT_EQ(c2.argb(), 0xFF04FF35);
}

/// \brief Test the set rgba method
TEST(color, set_rgba) {
    bardrix::color c1;
    c1.rgba(0xFFFFFFFF);
    EXPECT_EQ(c1.r(), 255);
    EXPECT_EQ(c1.g(), 255);
    EXPECT_EQ(c1.b(), 255);
    EXPECT_EQ(c1.a(), 255);

    bardrix::color c2;
    c2.rgba(0xFF35FF04);
    EXPECT_EQ(c2.r(), 255);
    EXPECT_EQ(c2.g(), 53);
    EXPECT_EQ(c2.b(), 255);
    EXPECT_EQ(c2.a(), 4);
}

/// \brief Test the set abgr method
TEST(color, set_abgr) {
    bardrix::color c1;
    c1.abgr(0xFFFFFFFF);
    EXPECT_EQ(c1.r(), 255);
    EXPECT_EQ(c1.g(), 255);
    EXPECT_EQ(c1.b(), 255);
    EXPECT_EQ(c1.a(), 255);

    bardrix::color c2;
    c2.abgr(0xFF35FF04  );
    EXPECT_EQ(c2.r(), 4);
    EXPECT_EQ(c2.g(), 255);
    EXPECT_EQ(c2.b(), 53);
    EXPECT_EQ(c2.a(), 255);
}

/// \brief Test the set argb method
TEST(color, set_argb) {
    bardrix::color c1;
    c1.argb(0xFFFFFFFF);
    EXPECT_EQ(c1.r(), 255);
    EXPECT_EQ(c1.g(), 255);
    EXPECT_EQ(c1.b(), 255);
    EXPECT_EQ(c1.a(), 255);

    bardrix::color c2;
    c2.argb(0xFF35FF04);
    EXPECT_EQ(c2.r(), 53);
    EXPECT_EQ(c2.g(), 255);
    EXPECT_EQ(c2.b(), 4);
    EXPECT_EQ(c2.a(), 255);
}

/// \brief Test the color addition
TEST(color, operator_plus) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    bardrix::color result = c1 + c2;
    EXPECT_EQ(result.abgr(), 0xFFFFFFFF);

    result = c1 + c1;
    EXPECT_EQ(result.abgr(), 0xFFFFFFFF);

    result = c2 + c2;
    EXPECT_EQ(result.abgr(), 0xFF6AFF08);

    result = c1 + c2 + c2;
    EXPECT_EQ(result.abgr(), 0xFFFFFFFF);
}

/// \brief Test the color addition with a scalar
TEST(color, operator_plus_scalar) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    bardrix::color c3 = c1 + 4;
    EXPECT_EQ(c3.abgr(), 0xFFFFFFFF);

    c3 = c1 + 255;
    EXPECT_EQ(c3.abgr(), 0xFFFFFFFF);

    c3 = 255 + c1;
    EXPECT_EQ(c3.abgr(), 0xFFFFFFFF);

    c3 = c1 + 4 + c1;
    EXPECT_EQ(c3.abgr(), 0xFFFFFFFF);

    c3 = 5 + c2;
    EXPECT_EQ(c3.abgr(), 0xFF3AFF09);
}

/// \brief Test the color addition to itself with a scalar
TEST(color, operator_plus_equal) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 5, 53, 12);

    c1 += c2;
    EXPECT_EQ(c1.abgr(), 0xFFFFFFFF);

    c1 = bardrix::color(255, 255, 255, 255);
    c1 += c1;
    EXPECT_EQ(c1.abgr(), 0xFFFFFFFF);

    c2 += c2;
    EXPECT_EQ(c2.abgr(), 0x186A0A08);

    c2 = bardrix::color(4, 255, 53, 255);
    c2 += 4;
    EXPECT_EQ(c2.abgr(), 0xFF39FF08);
}

/// \brief Test the color subtraction
TEST(color, operator_minus) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);
    bardrix::color c3(52, 12, 52, 45);

    bardrix::color result = c1 - c2;
    EXPECT_EQ(result.abgr(), 0x00CA00FB);

    result = c1 - c1;
    EXPECT_EQ(result.abgr(), 0);

    result = c2 - c2;
    EXPECT_EQ(result.abgr(), 0);

    result = c1 - c2 - c2;
    EXPECT_EQ(result.abgr(), 0x009500F7);

    result = c3 - c2;
    EXPECT_EQ(result.abgr(), 0x00000030);
}

/// \brief Test the color subtraction with a scalar
TEST(color, operator_minus_scalar) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    bardrix::color result = c1 - 4;
    EXPECT_EQ(result.abgr(), 0xFBFBFBFB);

    result = c1 - 255;
    EXPECT_EQ(result.abgr(), 0);

    result = 255 - c1;
    EXPECT_EQ(result.abgr(), 0);

    result = c1 - 4 - c1;
    EXPECT_EQ(result.abgr(), 0);

    result = 5 - c2;
    EXPECT_EQ(result.abgr(), 1);
}

/// \brief Test the color subtraction to itself with a scalar
TEST(color, operator_minus_equal) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);
    bardrix::color c3(52, 12, 52, 45);

    c1 -= c2;
    EXPECT_EQ(c1.abgr(), 0x00CA00FB);

    c1 = bardrix::color(255, 255, 255, 255);
    c1 -= c1;
    EXPECT_EQ(c1.abgr(), 0);

    c2 -= c2;
    EXPECT_EQ(c2.abgr(), 0);

    c3 -= c2;
    EXPECT_EQ(c3.abgr(), 0x2D340C34);
}

/// \brief Test the color multiplication
TEST(color, operator_minus_equal_scalar) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    c1 -= 4;
    EXPECT_EQ(c1.abgr(), 0xFBFBFBFB);

    c1 = bardrix::color(255, 255, 255, 255);
    c1 -= 255;
    EXPECT_EQ(c1.abgr(), 0);

    c2 -= 4;
    EXPECT_EQ(c2.abgr(), 0xFB31FB00);
}

/// \brief Test the color multiplication
TEST(color, operator_multiply) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    bardrix::color result = c2 * 4;
    EXPECT_EQ(result.abgr(), 0xFFD4FF10);

    result = c1 * 1.5;
    EXPECT_EQ(result.abgr(), 0xFFFFFFFF);

    result = 0.2 * c1;
    EXPECT_EQ(result.abgr(), 0x33333333);

    result = 0.2 * c2;
    EXPECT_EQ(result.abgr(), 0x330A3300);
}

/// \brief Test the color multiplication to itself
TEST(color, operator_multiply_equal) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    c1 *= 4;
    EXPECT_EQ(c1.abgr(), 0xFFFFFFFF);

    c2 *= 1.5;
    EXPECT_EQ(c2.abgr(), 0xFF4FFF06);

    c2 = bardrix::color(4, 255, 53, 255);
    c2 *= 0.2;
    EXPECT_EQ(c2.abgr(), 0x330A3300);
}

/// \brief Test the color multiplication by zero and negative values
TEST(color, operator_multiply_degenerate) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    bardrix::color result = c1 * 0;
    EXPECT_EQ(result.abgr(), 0);

    result = 0 * c1;
    EXPECT_EQ(result.abgr(), 0);

    result = c2 * -5;
    EXPECT_EQ(result.abgr(), 0);

    result = c2 * -0.1;
    EXPECT_EQ(result.abgr(), 0);

    result = { 2, 4, 5, 6 };
    result *= 0;
    EXPECT_EQ(result.abgr(), 0);
}

/// \brief Test the color division
TEST(color, operator_divide) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    bardrix::color result = c2 / 4;
    EXPECT_EQ(result.abgr(), 0x3F0D3F01);

    result = c1 / 1.5;
    EXPECT_EQ(result.abgr(), 0xAAAAAAAA);

    result = 0.2 / c1;
    EXPECT_EQ(result.abgr(), 0);

    result = c2 / 0.2;
    EXPECT_EQ(result.abgr(), 0xFFFFFF14);
}

/// \brief Test the color division to itself
TEST(color, operator_divide_equal) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    c1 /= 4;
    EXPECT_EQ(c1.abgr(), 0x3F3F3F3F);

    c2 /= 1.5;
    EXPECT_EQ(c2.abgr(), 0xAA23AA02);

    c2 = bardrix::color(4, 255, 53, 255);
    c2 /= 0.2;
    EXPECT_EQ(c2.abgr(), 0xFFFFFF14);
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

/// \brief Test the color modulo
TEST(color, operator_modulo) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    bardrix::color result = c2 % 4;
    EXPECT_EQ(result.abgr(), 0x03010300);

    result = c1 % 2;
    EXPECT_EQ(result.abgr(), 0x01010101);

    result = c2 % 2;
    EXPECT_EQ(result.abgr(), 0x01010100);

    result = c2 % 3;
    EXPECT_EQ(result.abgr(), 0x00020001);

    result = { 2, 4, 5, 6 };
    result = 2 % result;
    EXPECT_EQ(result.abgr(), 0x02020200);

    result = 253 % c2;
    EXPECT_EQ(result.abgr(), 0xFD29FD01);

    result = 253 % c1;
    EXPECT_EQ(result.abgr(), 0xFDFDFDFD);

    result = 53 % c2;
    EXPECT_EQ(result.abgr(), 0x35003501);

    result = 53 % c1;
    EXPECT_EQ(result.abgr(), 0x35353535);
}

/// \brief Test the color modulo to itself
TEST(color, operator_modulo_equal) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);

    c1 %= 2;
    EXPECT_EQ(c1.abgr(), 0x01010101);

    c2 %= 2;
    EXPECT_EQ(c2.abgr(), 0x01010100);

    c2 = bardrix::color(4, 255, 53, 255);
    c2 %= 3;
    EXPECT_EQ(c2.abgr(), 0x00020001);
}

/// \brief Test the color modulo by zero
TEST(color, operator_modulo_degenerate) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(0, 0, 0, 0);

    EXPECT_THROW(c1 % 0, std::invalid_argument);
    EXPECT_THROW(c2 % 0, std::invalid_argument);

    EXPECT_THROW(c1 %= 0, std::invalid_argument);
    EXPECT_THROW(c2 %= 0, std::invalid_argument);

    EXPECT_NO_THROW(123 % c1);
    EXPECT_THROW(123 % c2, std::invalid_argument);

    EXPECT_NO_THROW(0 % c1);
    EXPECT_THROW(0 % c2, std::invalid_argument);

    EXPECT_NO_THROW(c1 % 1);
    EXPECT_NO_THROW(c2 % 1);
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

/// \brief Tests the less than operator
TEST(color, operator_less_than) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);
    bardrix::color c3(4, 255, 53, 255);

    EXPECT_FALSE(c1 < c1);
    EXPECT_FALSE(c2 < c2);
    EXPECT_FALSE(c3 < c3);

    EXPECT_FALSE(c2 < c3);
    EXPECT_FALSE(c3 < c2);

    EXPECT_FALSE(c1 < c2);
    EXPECT_FALSE(c1 < c3);

    EXPECT_TRUE(c2 < c1);
    EXPECT_TRUE(c3 < c1);
}

/// \brief Tests the greater than operator
TEST(color, operator_greater_than) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);
    bardrix::color c3(4, 255, 53, 255);

    EXPECT_FALSE(c1 > c1);
    EXPECT_FALSE(c2 > c2);
    EXPECT_FALSE(c3 > c3);

    EXPECT_FALSE(c2 > c3);
    EXPECT_FALSE(c3 > c2);

    EXPECT_TRUE(c1 > c2);
    EXPECT_TRUE(c1 > c3);
}

/// \brief Tests the less than or equal operator
TEST(color, operator_less_than_or_equal) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);
    bardrix::color c3(4, 255, 53, 255);

    EXPECT_TRUE(c1 <= c1);
    EXPECT_TRUE(c2 <= c2);
    EXPECT_TRUE(c3 <= c3);

    EXPECT_TRUE(c2 <= c3);
    EXPECT_TRUE(c3 <= c2);

    EXPECT_FALSE(c1 <= c2);
    EXPECT_FALSE(c1 <= c3);

    EXPECT_TRUE(c2 <= c1);
    EXPECT_TRUE(c3 <= c1);
}

/// \brief Tests the greater than or equal operator
TEST(color, operator_greater_than_or_equal) {
    bardrix::color c1(255, 255, 255, 255);
    bardrix::color c2(4, 255, 53, 255);
    bardrix::color c3(4, 255, 53, 255);

    EXPECT_TRUE(c1 >= c1);
    EXPECT_TRUE(c2 >= c2);
    EXPECT_TRUE(c3 >= c3);

    EXPECT_TRUE(c2 >= c3);
    EXPECT_TRUE(c3 >= c2);

    EXPECT_TRUE(c1 >= c2);
    EXPECT_TRUE(c1 >= c3);

    EXPECT_FALSE(c2 >= c1);
    EXPECT_FALSE(c3 >= c1);
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