//
// Created by Bardio on 09/05/2024.
//

#include <bardrix/objects.h>

/// \brief Test the material default constructor
TEST(material, default_constructor) {
    bardrix::material material = bardrix::material();

    EXPECT_EQ(material.color, bardrix::color::white());
    EXPECT_EQ(material.get_ambient(), 0);
    EXPECT_EQ(material.get_diffuse(), 1);
    EXPECT_EQ(material.get_specular(), 0);
    EXPECT_EQ(material.get_shininess(), 0);
}

TEST(material, constructor_ambient_diffuse_shininess) {
    bardrix::material material = bardrix::material(0.1, 0.2, 0.3);

    EXPECT_EQ(material.color, bardrix::color::white());
    EXPECT_EQ(material.get_ambient(), 0.1);
    EXPECT_EQ(material.get_diffuse(), 0.2);
    EXPECT_EQ(material.get_specular(), 0.8);
    EXPECT_EQ(material.get_shininess(), 0.3);
}

/// \brief Test the material constructor
TEST(material, constructor) {
    bardrix::material material = bardrix::material(bardrix::color::red(), 0.1, 0.2, 0.3);

    EXPECT_EQ(material.color, bardrix::color::red());
    EXPECT_EQ(material.get_ambient(), 0.1);
    EXPECT_EQ(material.get_diffuse(), 0.2);
    EXPECT_EQ(material.get_specular(), 0.8);
    EXPECT_EQ(material.get_shininess(), 0.3);
}

/// \brief Test the material constructor with degenerate values
TEST(material, constructor_degenerate) {
    bardrix::material material = bardrix::material(bardrix::color::red(), -0.1, 1.2, -0.3);

    EXPECT_EQ(material.color, bardrix::color::red());
    EXPECT_EQ(material.get_ambient(), 0);
    EXPECT_EQ(material.get_diffuse(), 1);
    EXPECT_EQ(material.get_specular(), 0);
    EXPECT_EQ(material.get_shininess(), 0);
}

/// \brief Test the material set_ambient method
TEST(material, set_ambient) {
    bardrix::material material = bardrix::material(bardrix::color::red(), 0.1, 0.2, 0.3);

    material.set_ambient(0.5);
    EXPECT_EQ(material.get_ambient(), 0.5);

    material.set_ambient(-0.5);
    EXPECT_EQ(material.get_ambient(), 0);

    material.set_ambient(1.5);
    EXPECT_EQ(material.get_ambient(), 1);
}

/// \brief Test the material set_diffuse method
TEST(material, set_diffuse) {
    bardrix::material material = bardrix::material(bardrix::color::red(), 0.1, 0.2, 0.3);

    material.set_diffuse(0.5);
    EXPECT_EQ(material.get_diffuse(), 0.5);
    EXPECT_EQ(material.get_specular(), 0.5);

    material.set_diffuse(-0.5);
    EXPECT_EQ(material.get_diffuse(), 0);
    EXPECT_EQ(material.get_specular(), 1);

    material.set_diffuse(1.5);
    EXPECT_EQ(material.get_diffuse(), 1);
    EXPECT_EQ(material.get_specular(), 0);
}

/// \brief Test the material set_specular method
TEST(material, set_specular) {
    bardrix::material material = bardrix::material(bardrix::color::red(), 0.1, 0.2, 0.3);

    material.set_specular(0.5);
    EXPECT_EQ(material.get_specular(), 0.5);
    EXPECT_EQ(material.get_diffuse(), 0.5);

    material.set_specular(-0.5);
    EXPECT_EQ(material.get_specular(), 0);
    EXPECT_EQ(material.get_diffuse(), 1);

    material.set_specular(1.5);
    EXPECT_EQ(material.get_specular(), 1);
    EXPECT_EQ(material.get_diffuse(), 0);
}

/// \brief Test the material set_shininess method
TEST(material, set_shininess) {
    bardrix::material material = bardrix::material(bardrix::color::red(), 0.1, 0.2, 0.3);

    material.set_shininess(0.5);
    EXPECT_EQ(material.get_shininess(), 0.5);

    material.set_shininess(-0.5);
    EXPECT_EQ(material.get_shininess(), 0);

    material.set_shininess(1.5);
    EXPECT_EQ(material.get_shininess(), 1);
}
