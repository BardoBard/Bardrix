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

    EXPECT_EQ(box.min, top_left);
    EXPECT_EQ(box.max, bottom_right);
}

/// \brief Test the bounding_box inside method
TEST(bounding_box, inside) {
    bardrix::point3 min = bardrix::point3(-5.04,3.4,0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    EXPECT_TRUE(box.inside(bardrix::point3(0, 8, 3.45)));
    EXPECT_TRUE(box.inside(bardrix::point3(3.45, 7.5, 0)));
    EXPECT_TRUE(box.inside(bardrix::point3(-2, 8, 3.45)));
    EXPECT_TRUE(box.inside(bardrix::point3(2, 10, 3.45)));
    EXPECT_FALSE(box.inside(bardrix::point3(4.05, 9.74, 0)));
    EXPECT_FALSE(box.inside(bardrix::point3(-5.04, 6.17, 6.9)));
}

/// \brief Test the bounding_box inside method with another box
TEST(bounding_box, inside_box) {
    bardrix::point3 min = bardrix::point3(-5.04,3.4,0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    bardrix::point3 min2 = bardrix::point3(-5.04,3.4,0);
    bardrix::point3 max2 = bardrix::point3(4, 12.44, 6.84);
    EXPECT_TRUE(box.inside(bardrix::bounding_box(min2, max2)));

    min2 = bardrix::point3(-4, 2, 0);
    max2 = bardrix::point3(3, 11, 6);
    EXPECT_FALSE(box.inside(bardrix::bounding_box(min2, max2)));

    min2 = bardrix::point3(-4, 6, 0);
    max2 = bardrix::point3(3, 11, 6);
    EXPECT_TRUE(box.inside(bardrix::bounding_box(min2, max2)));

    min2 = bardrix::point3(-4, 6, 0);
    max2 = bardrix::point3(3, 13, 6);
    EXPECT_FALSE(box.inside(bardrix::bounding_box(min2, max2)));

    min2 = bardrix::point3(-4, 6, 0);
    max2 = bardrix::point3(3, 11, 7);
    EXPECT_FALSE(box.inside(bardrix::bounding_box(min2, max2)));

    min2 = bardrix::point3(-4, 6, 0);
    max2 = bardrix::point3(5, 11, 6);
    EXPECT_FALSE(box.inside(bardrix::bounding_box(min2, max2)));
}

/// \brief Test center of bounding_box
TEST(bounding_box, center) {
    bardrix::point3 min = bardrix::point3(-5.04,3.4,0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    bardrix::point3 center = box.center();

    EXPECT_EQ(center, bardrix::point3(-0.52, 7.92, 3.42));
}

/// \brief Test width of bounding_box
TEST(bounding_box, width) {
    bardrix::point3 min = bardrix::point3(-5.04,3.4,0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    EXPECT_EQ(box.width(), 9.04);
}

/// \brief Test height of bounding_box
TEST(bounding_box, height) {
    bardrix::point3 min = bardrix::point3(-5.04,3.4,0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    EXPECT_EQ(box.height(), 9.04);
}

/// \brief Test depth of bounding_box
TEST(bounding_box, depth) {
    bardrix::point3 min = bardrix::point3(-5.04,3.4,0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    EXPECT_EQ(box.depth(), 6.84);
}

/// \brief Test volume of bounding_box
TEST(bounding_box, volume) {
    bardrix::point3 min = bardrix::point3(-5.04,3.4,0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    EXPECT_EQ(box.volume(), 9.04 * 9.04 * 6.84);
}

/// \brief Test area of bounding_box
TEST(bounding_box, area) {
    bardrix::point3 min = bardrix::point3(-5.04,3.4,0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    EXPECT_EQ(box.area(), 2 * (9.04 * 9.04 + 9.04 * 6.84 + 9.04 * 6.84));
}

/// \brief Test diagonal of bounding_box
TEST(bounding_box, diagonal) {
    bardrix::point3 min = bardrix::point3(-5.04,3.4,0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    EXPECT_NEAR(box.diagonal(), 14.5, 0.02);
}

/// \brief Test the bounding_box is_hit method with ray
TEST(bounding_box, is_hit) {
    bardrix::point3 min = bardrix::point3(-5.04,3.4,0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);
    double distance = 100;

    bardrix::ray ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(-1, 2, 2), distance);
    EXPECT_TRUE(box.is_hit(ray));

    ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(-1.78419,2.6324,2), distance);
    EXPECT_TRUE(box.is_hit(ray));

    ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(0.74519,2.01385,2), distance);
    EXPECT_TRUE(box.is_hit(ray));

    ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(0.10442,1.2,1.73264), distance);
    EXPECT_TRUE(box.is_hit(ray));

    ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(1.39641,1.79423,2), distance);
    EXPECT_TRUE(box.is_hit(ray));

    ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(1.39641,1.79423,3.62911), distance);
    EXPECT_FALSE(box.is_hit(ray));

    ray = bardrix::ray(bardrix::point3(-12,4,6), bardrix::vector3(0.10442,1.016,2), distance);
    EXPECT_FALSE(box.is_hit(ray));
}

/// \brief Test the bounding_box is_hit method with ray negative x, y, z directions
TEST(bounding_box, is_hit_negative_direction) {
    bardrix::point3 min = bardrix::point3(-5.04,3.4,0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);
    double distance = 100;

    //9.66171,10.84802,4

    bardrix::ray ray = bardrix::ray(bardrix::point3(2.7942,6.20428,7.47399), bardrix::vector3(-11.02986,0.26419,-1.64038), distance);
    EXPECT_TRUE(box.is_hit(ray));

    ray = bardrix::ray(bardrix::point3(2,23,-4), bardrix::vector3(-1,-2,0.7), distance);
    EXPECT_TRUE(box.is_hit(ray));

    ray = bardrix::ray(bardrix::point3(-2.53588,9.58673,-4), bardrix::vector3(-0.2,-0.1,1), distance);
    EXPECT_TRUE(box.is_hit(ray));

    ray = bardrix::ray(bardrix::point3(0, 20, 4), bardrix::vector3(-1, -2, -2), distance);
    EXPECT_FALSE(box.is_hit(ray));

    ray = bardrix::ray(bardrix::point3(2, 23, -2), bardrix::vector3(9.64699,2.19987,-1.64038), distance);
    EXPECT_FALSE(box.is_hit(ray));

    ray = bardrix::ray(bardrix::point3(2, 23, -2), bardrix::vector3(-28.86337,-12.71138,23.94488), distance);
    EXPECT_FALSE(box.is_hit(ray));
}

/// \brief Test the bounding_box is_hit method with distances of small values
TEST(bounding_box, is_hit_small_distance) {
    bardrix::point3 min = bardrix::point3(-5.04,3.4,0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);
    double distance = 0.1;

    bardrix::ray ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(-1, 2, 2), 0.5);
    EXPECT_FALSE(box.is_hit(ray));

    ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(-1.78419,2.6324,2), 1);
    EXPECT_FALSE(box.is_hit(ray));

    ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(0.74519,2.01385,2), 0);
    EXPECT_FALSE(box.is_hit(ray));
}

/// \brief Test the bounding_box is_hit method where the ray is inside the box
TEST(bounding_box, is_hit_inside) {
    bardrix::point3 min = bardrix::point3(-5.04,3.4,0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);
    double distance = 100;

    bardrix::ray ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(1, 2, 2), distance);
    EXPECT_TRUE(box.is_hit(ray));

    ray = bardrix::ray(box.center(), bardrix::vector3(1.78419,2.6324,2), distance);
    EXPECT_TRUE(box.is_hit(ray));
    EXPECT_TRUE(box.inside(ray.position));
    ray.set_length(0);
    EXPECT_TRUE(box.inside(ray.position));
}