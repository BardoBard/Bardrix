//
// Created by Bard on 20/03/2024.
//

#include <bardrix/math.h>

/// \brief Test the degrees to radians
TEST(math, degrees_to_radians) {
    EXPECT_EQ(bardrix::degrees_to_radians(0), 0);
    EXPECT_EQ(bardrix::degrees_to_radians(90), bardrix::M_PI / 2);
    EXPECT_EQ(bardrix::degrees_to_radians(180), bardrix::M_PI);
    EXPECT_EQ(bardrix::degrees_to_radians(270), 3 * bardrix::M_PI / 2);
    EXPECT_EQ(bardrix::degrees_to_radians(360), 2 * bardrix::M_PI);
}

/// \brief Test the degenerate cases of degrees to radians
TEST(math, degrees_to_radians_degenerate) {
    EXPECT_EQ(bardrix::degrees_to_radians(-0), -0);
    EXPECT_EQ(bardrix::degrees_to_radians(-90), -bardrix::M_PI / 2);
    EXPECT_EQ(bardrix::degrees_to_radians(-180), -bardrix::M_PI);
    EXPECT_EQ(bardrix::degrees_to_radians(-270), -3 * bardrix::M_PI / 2);
    EXPECT_TRUE(bardrix::nearly_equal(bardrix::degrees_to_radians(4345923), 4345923 * bardrix::M_PI / 180));
    EXPECT_TRUE(bardrix::nearly_equal(bardrix::degrees_to_radians(-239858), -239858 * bardrix::M_PI / 180));
}

/// \brief Test the radians to degrees
TEST(math, radians_to_degrees) {
    EXPECT_EQ(bardrix::radians_to_degrees(0), 0);
    EXPECT_EQ(bardrix::radians_to_degrees(bardrix::M_PI / 2), 90);
    EXPECT_EQ(bardrix::radians_to_degrees(bardrix::M_PI), 180);
    EXPECT_EQ(bardrix::radians_to_degrees(3 * bardrix::M_PI / 2), 270);
    EXPECT_EQ(bardrix::radians_to_degrees(2 * bardrix::M_PI), 360);
}

/// \brief Test the degenerate cases of radians to degrees
TEST(math, radians_to_degrees_degenerate) {
    EXPECT_EQ(bardrix::radians_to_degrees(-0), -0);
    EXPECT_EQ(bardrix::radians_to_degrees(-bardrix::M_PI / 2), -90);
    EXPECT_EQ(bardrix::radians_to_degrees(-bardrix::M_PI), -180);
    EXPECT_EQ(bardrix::radians_to_degrees(-3 * bardrix::M_PI / 2), -270);
    EXPECT_EQ(bardrix::radians_to_degrees(4345923), 4345923 * 180 / bardrix::M_PI);
    EXPECT_EQ(bardrix::radians_to_degrees(-239858), -239858 * 180 / bardrix::M_PI);
}

/// \brief Test the nearly equal function
TEST(math, nearly_equal) {
    bardrix::epsilon = 0.0001;
    EXPECT_TRUE(bardrix::nearly_equal(0, 0));
    EXPECT_TRUE(bardrix::nearly_equal(0, 0.0001));
    EXPECT_TRUE(bardrix::nearly_equal(0.0001, 0));
    EXPECT_TRUE(bardrix::nearly_equal(0.0001, 0.0002));
    EXPECT_TRUE(bardrix::nearly_equal(0.0002, 0.0001));
    EXPECT_TRUE(bardrix::nearly_equal(0.0002, 0.0003));
    EXPECT_TRUE(bardrix::nearly_equal(0.0003, 0.0002));
    EXPECT_TRUE(bardrix::nearly_equal(523.0001, 523));
    EXPECT_TRUE(bardrix::nearly_equal(523, 523.0001));
    EXPECT_TRUE(bardrix::nearly_equal(537458.0001, 537458));

    EXPECT_FALSE(bardrix::nearly_equal(0, 0.0002));
    EXPECT_FALSE(bardrix::nearly_equal(0.0002, 0));
    EXPECT_FALSE(bardrix::nearly_equal(523.0002, 523));
    EXPECT_FALSE(bardrix::nearly_equal(523, 523.0002));
    EXPECT_FALSE(bardrix::nearly_equal(537458938.0002, 537458938));
}