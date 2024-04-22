//
// Created by Bardio on 30/03/2024.
//

#include <bardrix/light.h>
#include <bardrix/color.h>

/// \brief Test light constructors
TEST(light, constructors) {
    bardrix::light light1;
    EXPECT_EQ(light1.position, bardrix::point3());
    EXPECT_EQ(light1.get_intensity(), 1);
    EXPECT_EQ(light1.color, bardrix::color::white());

    bardrix::light light2(bardrix::point3(1, 2, 3), 0.5, bardrix::color::green());
    EXPECT_EQ(light2.position, bardrix::point3(1, 2, 3));
    EXPECT_EQ(light2.get_intensity(), 0.5);
    EXPECT_EQ(light2.color, bardrix::color::green());
}

/// \brief Test degenerate cases of light constructors
TEST(light, constructors_degenerate) {
    bardrix::light light1(bardrix::point3(1, 2, 3), -0.5, bardrix::color::green());
    EXPECT_EQ(light1.get_intensity(), 0);

    bardrix::light light2(bardrix::point3(1, 2, 3), 0, bardrix::color::green());
    EXPECT_EQ(light2.get_intensity(), 0);
}

/// \brief Test light inverse square law
TEST(light, inverse_square_law_point) {
    bardrix::light light1;
    EXPECT_EQ(light1.inverse_square_law(bardrix::point3(1, -24, 3)), 1 / 586.0);

    light1.set_intensity(25);
    EXPECT_EQ(light1.inverse_square_law(bardrix::point3(192, -23, 6)), 25 / 37429.0);
    EXPECT_EQ(light1.inverse_square_law(bardrix::point3(1, 1, 1)), 25 / 3.0);

    bardrix::light light2(bardrix::point3(1, 1, 1), 0.5, bardrix::color::green());
    EXPECT_EQ(light2.inverse_square_law(bardrix::point3(0, 0, 0)), 0.5 / 3.0);
    EXPECT_EQ(light2.inverse_square_law(bardrix::point3(-1, 0, 0)), 0.5 / 6.0);
    EXPECT_EQ(light2.inverse_square_law(bardrix::point3(24, 1, 23)), 0.5 / 1013.0);
    EXPECT_EQ(light2.inverse_square_law(bardrix::point3(-3, 3, -4)), 0.5 / 45.0);
}

/// \brief Test light inverse square law with distance
TEST(light, inverse_square_law_distance) {
    bardrix::light light1;
    EXPECT_EQ(light1.inverse_square_law(1), 1);
    EXPECT_EQ(light1.inverse_square_law(25), 1 / (25.0 * 25.0));

    light1.set_intensity(25);
    EXPECT_EQ(light1.inverse_square_law(1), 25);
    EXPECT_EQ(light1.inverse_square_law(25), 25 / (25.0 * 25.0));

    bardrix::light light2(bardrix::point3(1, 1, 1), 0.5, bardrix::color::green());
    EXPECT_EQ(light2.inverse_square_law(1), 0.5);
    EXPECT_EQ(light2.inverse_square_law(25), 0.5 / (25.0 * 25.0));
}

/// \brief Test light inverse square law with distance degenerate cases
TEST(light, inverse_square_law_distance_degenerate) {
    bardrix::light light1;
    EXPECT_EQ(light1.inverse_square_law(0), HUGE_VAL);
    EXPECT_EQ(light1.inverse_square_law(-0), HUGE_VAL);
    EXPECT_EQ(light1.inverse_square_law(-1), 1);
    EXPECT_EQ(light1.inverse_square_law(-25), 1 / (25.0 * 25.0));

    light1.set_intensity(25);
    EXPECT_EQ(light1.inverse_square_law(-0), HUGE_VAL);
    EXPECT_EQ(light1.inverse_square_law(-1), 25);
    EXPECT_EQ(light1.inverse_square_law(-25), 25 / (25.0 * 25.0));

    bardrix::light light2(bardrix::point3(1, 1, 1), 0.5, bardrix::color::green());
    EXPECT_EQ(light2.inverse_square_law(-0), HUGE_VAL);
    EXPECT_EQ(light2.inverse_square_law(-1), 0.5);
    EXPECT_EQ(light2.inverse_square_law(-25), 0.5 / (25.0 * 25.0));
}

/// \brief Test light equality
TEST(light, equality) {
    bardrix::light light1;
    bardrix::light light2;
    EXPECT_TRUE(light1 == light2);

    bardrix::light light3(bardrix::point3(1, 2, 3), 0.5, bardrix::color::green());
    bardrix::light light4(bardrix::point3(1, 2, 3), 0.5, bardrix::color::green());
    EXPECT_TRUE(light3 == light4);

    bardrix::light light5(bardrix::point3(1, 2, 3), 0.5, bardrix::color::green());
    bardrix::light light6(bardrix::point3(1, 2, 3), 0.5, bardrix::color::red());
    EXPECT_FALSE(light5 == light6);

    bardrix::light light7(bardrix::point3(1, 2, 3), 0.5, bardrix::color::green());
    bardrix::light light8(bardrix::point3(1, 2, 3), 0.6, bardrix::color::green());
    EXPECT_FALSE(light7 == light8);

    bardrix::light light9(bardrix::point3(1, 2, 3), 0.5, bardrix::color::green());
    bardrix::light light10(bardrix::point3(1, 2, 3), 0.5, bardrix::color::green());
    light10.set_intensity(0.6);
    EXPECT_FALSE(light9 == light10);
}

/// \brief Test light inequality
TEST(light, inequality) {
    bardrix::light light1;
    bardrix::light light2;
    EXPECT_FALSE(light1 != light2);

    bardrix::light light3(bardrix::point3(1, 2, 3), 0.5, bardrix::color::green());
    bardrix::light light4(bardrix::point3(1, 2, 3), 0.5, bardrix::color::green());
    EXPECT_FALSE(light3 != light4);

    bardrix::light light5(bardrix::point3(1, 2, 3), 0.5, bardrix::color::green());
    bardrix::light light6(bardrix::point3(1, 2, 3), 0.5, bardrix::color::red());
    EXPECT_TRUE(light5 != light6);

    bardrix::light light7(bardrix::point3(1, 2, 3), 0.5, bardrix::color::green());
    bardrix::light light8(bardrix::point3(1, 2, 3), 0.6, bardrix::color::green());
    EXPECT_TRUE(light7 != light8);

    bardrix::light light9(bardrix::point3(1, 2, 3), 0.5, bardrix::color::green());
    bardrix::light light10(bardrix::point3(1, 2, 3), 0.5, bardrix::color::green());
    light10.set_intensity(0.6);
    EXPECT_TRUE(light9 != light10);
}

/// \brief Test print light
TEST(light, print) {
    bardrix::light light1(bardrix::point3(1, 2, 3), 0, bardrix::color::green());
    std::ostringstream os1;
    light1.print(os1);
    EXPECT_EQ(os1.str(), "Light: (1, 2, 3), Intensity: 0, Color: (0, 255, 0, 255)");
}

/// \brief Test print light with stream operator
TEST(light, operator_stream) {
    bardrix::light light1(bardrix::point3(1, 2, 3), 0, bardrix::color::green());
    std::ostringstream os1;
    os1 << light1;
    EXPECT_EQ(os1.str(), "Light: (1, 2, 3), Intensity: 0, Color: (0, 255, 0, 255)");
}