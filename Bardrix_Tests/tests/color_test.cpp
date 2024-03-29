//
// Created by Bardio on 29/03/2024.
//

#include <bardrix/color.h>

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