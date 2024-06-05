//
// Created by Bardio on 09/05/2024.
//

#include <bardrix/objects.h>

/// MATERIAL

/// \brief Test the material default constructor
TEST(material, default_constructor) {
    bardrix::material material = bardrix::material();

    EXPECT_EQ(material.color, bardrix::color::white());
    EXPECT_EQ(material.get_ambient(), 0);
    EXPECT_EQ(material.get_diffuse(), 1);
    EXPECT_EQ(material.get_specular(), 0);
    EXPECT_EQ(material.get_shininess(), 1);
}

TEST(material, constructor_ambient_diffuse_shininess) {
    bardrix::material material = bardrix::material(0.1, 0.2, 0.3, 1);

    EXPECT_EQ(material.color, bardrix::color::white());
    EXPECT_EQ(material.get_ambient(), 0.1);
    EXPECT_EQ(material.get_diffuse(), 0.2);
    EXPECT_EQ(material.get_specular(), 0.3);
    EXPECT_EQ(material.get_shininess(), 1);
}

/// \brief Test the material constructor
TEST(material, constructor) {
    bardrix::material material = bardrix::material(0.1, 0.2, 0.3, 1, bardrix::color::red());

    EXPECT_EQ(material.color, bardrix::color::red());
    EXPECT_EQ(material.get_ambient(), 0.1);
    EXPECT_EQ(material.get_diffuse(), 0.2);
    EXPECT_EQ(material.get_specular(), 0.3);
    EXPECT_EQ(material.get_shininess(), 1);
}

/// \brief Test the material constructor with degenerate values
TEST(material, constructor_degenerate) {
    bardrix::material material = bardrix::material(-0.1, 1.2, -0.3, 0, bardrix::color::red());

    EXPECT_EQ(material.color, bardrix::color::red());
    EXPECT_EQ(material.get_ambient(), 0);
    EXPECT_EQ(material.get_diffuse(), 1);
    EXPECT_EQ(material.get_specular(), 0);
    EXPECT_EQ(material.get_shininess(), 1);
}

/// \brief Test the material set_ambient method
TEST(material, set_ambient) {
    bardrix::material material = bardrix::material(0.1, 0.2, 0.3, 1);

    material.set_ambient(0.5);
    EXPECT_EQ(material.get_ambient(), 0.5);

    material.set_ambient(-0.5);
    EXPECT_EQ(material.get_ambient(), 0);

    material.set_ambient(1.5);
    EXPECT_EQ(material.get_ambient(), 1);
}

/// \brief Test the material set_diffuse method
TEST(material, set_diffuse) {
    bardrix::material material = bardrix::material(0.1, 0.2, 0.3, 1);

    material.set_diffuse(0.5);
    EXPECT_EQ(material.get_diffuse(), 0.5);

    material.set_diffuse(-0.5);
    EXPECT_EQ(material.get_diffuse(), 0);

    material.set_diffuse(1.5);
    EXPECT_EQ(material.get_diffuse(), 1);
}

/// \brief Test the material set_specular method
TEST(material, set_specular) {
    bardrix::material material = bardrix::material(0.1, 0.2, 0.3, 1);

    material.set_specular(0.5);
    EXPECT_EQ(material.get_specular(), 0.5);

    material.set_specular(-0.5);
    EXPECT_EQ(material.get_specular(), 0);

    material.set_specular(1.5);
    EXPECT_EQ(material.get_specular(), 1);
}

/// \brief Test the material set_shininess method
TEST(material, set_shininess) {
    bardrix::material material = bardrix::material(0.1, 0.2, 0.3, 1);

    material.set_shininess(0.5);
    EXPECT_EQ(material.get_shininess(), 1);

    material.set_shininess(-0.5);
    EXPECT_EQ(material.get_shininess(), 1);

    material.set_shininess(1.5);
    EXPECT_EQ(material.get_shininess(), 1.5);
}

/// BOUNDING BOX

/// \brief Test the bounding_box constructor
TEST(bounding_box, constructor) {
    bardrix::point3 top_left = bardrix::point3(0, 0, 0);
    bardrix::point3 bottom_right = bardrix::point3(1, 1, 1);
    bardrix::bounding_box box = bardrix::bounding_box(top_left, bottom_right);

    EXPECT_EQ(box.top_left, top_left);
    EXPECT_EQ(box.bottom_right, bottom_right);
}

/// \brief Test the bounding_box contains method
TEST(bounding_box, contains) {
    bardrix::point3 top_left = bardrix::point3(-5.04, 6.17, 6.9);
    bardrix::point3 bottom_right = bardrix::point3(4.05, 9.74, 0);
    bardrix::bounding_box box = bardrix::bounding_box(top_left, bottom_right);

    EXPECT_TRUE(box.contains(bardrix::point3(-5.04, 6.17, 6.9)));
    EXPECT_TRUE(box.contains(bardrix::point3(4.05, 9.74, 0)));
    EXPECT_TRUE(box.contains(bardrix::point3(0, 8, 3.45)));
    EXPECT_FALSE(box.contains(bardrix::point3(-2, 8, 3.45)));
    EXPECT_FALSE(box.contains(bardrix::point3(2, 10, 3.45)));
    EXPECT_TRUE(box.contains(bardrix::point3(3.45, 7.5, 0)));
}