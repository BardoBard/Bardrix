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

/// \brief Test the material equality operator
TEST(material, equality_operator) {
    bardrix::material material1 = bardrix::material(0.1, 0.2, 0.3, 1);
    bardrix::material material2 = bardrix::material(0.1, 0.2, 0.3, 1);

    EXPECT_EQ(material1, material2);

    material2.set_ambient(0.5);
    EXPECT_NE(material1, material2);

    material2 = bardrix::material(0.1, 0.2, 0.3, 1);
    material2.set_diffuse(0.5);
    EXPECT_NE(material1, material2);

    material2 = bardrix::material(0.1, 0.2, 0.3, 1);
    material2.set_specular(0.5);
    EXPECT_NE(material1, material2);

    material2 = bardrix::material(0.1, 0.2, 0.3, 1);
    material2.set_shininess(1.5);
    EXPECT_NE(material1, material2);

    material2 = bardrix::material(0.1, 0.2, 0.3, 1);
    material2.color = bardrix::color::red();
    EXPECT_NE(material1, material2);
}

/// \brief Test the material inequality operator
TEST(material, inequality_operator) {
    bardrix::material material1 = bardrix::material(0.1, 0.2, 0.3, 1);
    bardrix::material material2 = bardrix::material(0.1, 0.2, 0.3, 1);

    EXPECT_FALSE(material1 != material2);

    material2.set_ambient(0.5);
    EXPECT_TRUE(material1 != material2);

    material2 = bardrix::material(0.1, 0.2, 0.3, 1);
    material2.set_diffuse(0.5);
    EXPECT_TRUE(material1 != material2);

    material2 = bardrix::material(0.1, 0.2, 0.3, 1);
    material2.set_specular(0.5);
    EXPECT_TRUE(material1 != material2);

    material2 = bardrix::material(0.1, 0.2, 0.3, 1);
    material2.set_shininess(1.5);
    EXPECT_TRUE(material1 != material2);

    material2 = bardrix::material(0.1, 0.2, 0.3, 1);
    material2.color = bardrix::color::red();
    EXPECT_TRUE(material1 != material2);
}

/// BOUNDING BOX

/// \brief Test the bounding_box constructor
TEST(bounding_box, constructor) {
    bardrix::point3 top_left = bardrix::point3(0, 0, 0);
    bardrix::point3 bottom_right = bardrix::point3(1, 1, 1);

    bardrix::bounding_box box = bardrix::bounding_box(top_left, bottom_right);
    EXPECT_EQ(box.get_min(), top_left);
    EXPECT_EQ(box.get_max(), bottom_right);

    box = bardrix::bounding_box(bottom_right, top_left);
    EXPECT_EQ(box.get_min(), top_left);
    EXPECT_EQ(box.get_max(), bottom_right);
}

/// \brief Test the set_min_max method of bounding_box
TEST(bounding_box, set_min_max) {
    bardrix::point3 top_left = bardrix::point3(0, 0, 0);
    bardrix::point3 bottom_right = bardrix::point3(1, 1, 1);

    bardrix::bounding_box box = bardrix::bounding_box(top_left, bottom_right);
    EXPECT_EQ(box.get_min(), top_left);
    EXPECT_EQ(box.get_max(), bottom_right);

    bardrix::point3 top_left2 = bardrix::point3(1, 1, 1);
    bardrix::point3 bottom_right2 = bardrix::point3(0, 0, 0);

    box.set_min_max(top_left2, bottom_right2);
    EXPECT_EQ(box.get_min(), bottom_right2);
    EXPECT_EQ(box.get_max(), top_left2);
}

/// \brief Test the bounding_box inside method
TEST(bounding_box, inside) {
    bardrix::point3 min = bardrix::point3(-5.04, 3.4, 0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    EXPECT_TRUE(box.inside(bardrix::point3(0, 8, 3.45)));
    EXPECT_TRUE(box.inside(bardrix::point3(3.45, 7.5, 0)));
    EXPECT_TRUE(box.inside(bardrix::point3(-2, 8, 3.45)));
    EXPECT_TRUE(box.inside(bardrix::point3(2, 10, 3.45)));
    EXPECT_FALSE(box.inside(bardrix::point3(4.05, 9.74, 0)));
    EXPECT_FALSE(box.inside(bardrix::point3(-5.04, 6.17, 6.9)));
}
/// \brief Test the edge case of the bounding_box inside method
TEST(bounding_box, inside_edge_cases) {
    bardrix::point3 min = bardrix::point3(-5.04, 3.4, 0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    EXPECT_TRUE(box.inside(bardrix::point3(-5.04, 3.4, 0)));
    EXPECT_TRUE(box.inside(bardrix::point3(4, 12.44, 6.84)));
    EXPECT_TRUE(box.inside(bardrix::point3(-5.04, 12.44, 6.84)));
    EXPECT_TRUE(box.inside(bardrix::point3(4, 3.4, 6.84)));
    EXPECT_TRUE(box.inside(bardrix::point3(-5.04, 3.4, 6.84)));
    EXPECT_TRUE(box.inside(bardrix::point3(4, 12.44, 0)));
    EXPECT_TRUE(box.inside(bardrix::point3(-5.04, 6.17, 4)));

    EXPECT_FALSE(box.inside(bardrix::point3(-5.05, 3.4, 0)));
    EXPECT_FALSE(box.inside(bardrix::point3(4.01, 12.44, 6.84)));
    EXPECT_FALSE(box.inside(bardrix::point3(-5.04, 12.45, 6.84)));
    EXPECT_FALSE(box.inside(bardrix::point3(4, 3.4, 6.85)));
}

/// \brief Test the bounding_box inside method with another box
TEST(bounding_box, inside_box) {
    bardrix::point3 min = bardrix::point3(-5.04, 3.4, 0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    bardrix::point3 min2 = bardrix::point3(-5.04, 3.4, 0);
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

    // Test the inside method with a box that is inside the other box
    EXPECT_TRUE(box.inside(bardrix::bounding_box(min, max)));

    EXPECT_TRUE(
            bardrix::bounding_box({ 1, 2, 3 }, { 1, 2, 3 }).inside(bardrix::bounding_box({ 1, 2, 3 }, { 1, 2, 3 })));
}

/// \brief Test the bounding_box inside method with another box with edge cases
TEST(bounding_box, inside_box_edge_cases) {
    bardrix::point3 min = bardrix::point3(-5.04, 3.4, 0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    bardrix::point3 min2 = bardrix::point3(-5.04, 3.4, 0);
    bardrix::point3 max2 = bardrix::point3(4, 12.44, 6.84);
    EXPECT_TRUE(box.inside(bardrix::bounding_box(min2, max2)));

    // Different box.x
    EXPECT_FALSE(box.inside(bardrix::bounding_box({ -5.05, 3.4, 0 }, { 4, 12.44, 6.84 })));
    EXPECT_FALSE(box.inside(bardrix::bounding_box({ 4.01, 3.4, 0 }, { 4, 12.44, 6.84 })));

    // Different box.y
    EXPECT_FALSE(box.inside(bardrix::bounding_box({ -5.04, 3.39, 0 }, { 4, 12.44, 6.84 })));
    EXPECT_TRUE(box.inside(bardrix::bounding_box({ -5.04, 12.43, 0 }, { 4, 12.44, 6.84 })));

    // Different box.z
    EXPECT_TRUE(box.inside(bardrix::bounding_box({ -5.04, 3.4, 6 }, { 4, 12.44, 6.84 })));
    EXPECT_TRUE(box.inside(bardrix::bounding_box({ -5.04, 3.4, 0 }, { 4, 12.44, 0 })));
}

/// \brief Test center of bounding_box
TEST(bounding_box, center) {
    bardrix::point3 min = bardrix::point3(-5.04, 3.4, 0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    bardrix::point3 center = box.center();

    EXPECT_EQ(center, bardrix::point3(-0.52, 7.92, 3.42));
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 1, 2, 3 }).center(), bardrix::point3(1, 2, 3));
    EXPECT_EQ(bardrix::bounding_box({ 0, 0, 0 }, { 0, 0, 0 }).center(), bardrix::point3(0, 0, 0));
}

/// \brief Test width of bounding_box
TEST(bounding_box, width) {
    bardrix::point3 min = bardrix::point3(-5.04, 3.4, 0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    EXPECT_EQ(box.width(), 9.04);
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 3, 4, 5 }).width(), 2);
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 1, 4, 5 }).width(), 0);
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 1, 2, 5 }).width(), 0);
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 1, 2, 3 }).width(), 0);
    EXPECT_EQ(bardrix::bounding_box({ 0, 0, 0 }, { 0, 0, 0 }).width(), 0);
}

/// \brief Test height of bounding_box
TEST(bounding_box, height) {
    bardrix::point3 min = bardrix::point3(-5.04, 3.4, 0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    EXPECT_EQ(box.height(), 9.04);
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 3, 4, 5 }).height(), 2);
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 1, 4, 5 }).height(), 2);
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 1, 2, 5 }).height(), 0);
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 1, 2, 3 }).height(), 0);
    EXPECT_EQ(bardrix::bounding_box({ 0, 0, 0 }, { 0, 0, 0 }).height(), 0);
}

/// \brief Test depth of bounding_box
TEST(bounding_box, depth) {
    bardrix::point3 min = bardrix::point3(-5.04, 3.4, 0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    EXPECT_EQ(box.depth(), 6.84);
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 3, 4, 5 }).depth(), 2);
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 1, 4, 5 }).depth(), 2);
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 1, 2, 5 }).depth(), 2);
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 1, 2, 3 }).depth(), 0);
    EXPECT_EQ(bardrix::bounding_box({ 0, 0, 0 }, { 0, 0, 0 }).depth(), 0);
}

/// \brief Test volume of bounding_box
TEST(bounding_box, volume) {
    bardrix::point3 min = bardrix::point3(-5.04, 3.4, 0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    EXPECT_EQ(box.volume(), 9.04 * 9.04 * 6.84);
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 3, 4, 5 }).volume(), 2 * 2 * 2);
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 1, 4, 5 }).volume(), 0);
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 1, 2, 5 }).volume(), 0);
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 1, 2, 3 }).volume(), 0);
    EXPECT_EQ(bardrix::bounding_box({ 0, 0, 0 }, { 0, 0, 0 }).volume(), 0);
}

/// \brief Test area of bounding_box
TEST(bounding_box, area) {
    bardrix::point3 min = bardrix::point3(-5.04, 3.4, 0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    EXPECT_EQ(box.area(), 2 * (9.04 * 9.04 + 9.04 * 6.84 + 9.04 * 6.84));
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 3, 4, 5 }).area(), 2 * (2 * 2 + 2 * 2 + 2 * 2));
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 1, 4, 5 }).area(), 2 * (2 * 2));
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 1, 2, 5 }).area(), 0);
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 1, 2, 3 }).area(), 0);
    EXPECT_EQ(bardrix::bounding_box({ 0, 0, 0 }, { 0, 0, 0 }).area(), 0);
}

/// \brief Test diagonal of bounding_box
TEST(bounding_box, diagonal) {
    bardrix::point3 min = bardrix::point3(-5.04, 3.4, 0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    EXPECT_NEAR(box.diagonal(), 14.5, 0.02);
    EXPECT_NEAR(bardrix::bounding_box({ 1, 2, 3 }, { 3, 4, 5 }).diagonal(), 3.46, 0.01);
    EXPECT_NEAR(bardrix::bounding_box({ 1, 2, 3 }, { 1, 4, 5 }).diagonal(), 2.82, 0.01);
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 1, 2, 5 }).diagonal(), 2);
    EXPECT_EQ(bardrix::bounding_box({ 1, 2, 3 }, { 1, 2, 3 }).diagonal(), 0);
    EXPECT_EQ(bardrix::bounding_box({ 0, 0, 0 }, { 0, 0, 0 }).diagonal(), 0);
}

/// \brief Test the merged of two bounding boxes
TEST(bounding_box, merged) {
    bardrix::point3 min1 = bardrix::point3(-5.04, 3.4, 0);
    bardrix::point3 max1 = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box1 = bardrix::bounding_box(min1, max1);

    bardrix::point3 min2 = bardrix::point3(-4, 2, 1);
    bardrix::point3 max2 = bardrix::point3(3, 11, 7);
    bardrix::bounding_box box2 = bardrix::bounding_box(min2, max2);

    bardrix::bounding_box merged = box1.merged(box2);
    EXPECT_EQ(merged.get_min(), bardrix::point3(-5.04, 2, 0));
    EXPECT_EQ(merged.get_max(), bardrix::point3(4, 12.44, 7));

    min2 = bardrix::point3(-6, 6, -1);
    max2 = bardrix::point3(7, 14, 2);
    box2 = bardrix::bounding_box(min2, max2);

    merged = box1.merged(box2);
    EXPECT_EQ(merged.get_min(), bardrix::point3(-6, 3.4, -1));
    EXPECT_EQ(merged.get_max(), bardrix::point3(7, 14, 6.84));

    merged = bardrix::bounding_box({ 1, 2, 3 }, { 3, 4, 5 }).merged(bardrix::bounding_box({ 1, 2, 3 }, { 3, 4, 5 }));
    EXPECT_EQ(merged.get_min(), bardrix::point3(1, 2, 3));
    EXPECT_EQ(merged.get_max(), bardrix::point3(3, 4, 5));

    merged = bardrix::bounding_box({ 0, 0, 0 }, { 1, 2, 3 }).merged(bardrix::bounding_box({ 0, 0, 0 }, { 0, 0, 0 }));
    EXPECT_EQ(merged.get_min(), bardrix::point3(0, 0, 0));
    EXPECT_EQ(merged.get_max(), bardrix::point3(1, 2, 3));

    merged = bardrix::bounding_box({ 0, 0, 0 }, { 0, 0, 0 }).merged(bardrix::bounding_box({ 0, 0, 0 }, { 0, 0, 0 }));
    EXPECT_EQ(merged.get_min(), bardrix::point3(0, 0, 0));
    EXPECT_EQ(merged.get_max(), bardrix::point3(0, 0, 0));
}

/// \brief Test the merge method of bounding_box
TEST(bounding_box, merge) {
    bardrix::point3 min1 = bardrix::point3(-5.04, 3.4, 0);
    bardrix::point3 max1 = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box1 = bardrix::bounding_box(min1, max1);

    bardrix::point3 min2 = bardrix::point3(-4, 2, 1);
    bardrix::point3 max2 = bardrix::point3(3, 11, 7);
    bardrix::bounding_box box2 = bardrix::bounding_box(min2, max2);

    box1.merge(box2);
    EXPECT_EQ(box1.get_min(), bardrix::point3(-5.04, 2, 0));
    EXPECT_EQ(box1.get_max(), bardrix::point3(4, 12.44, 7));

    min2 = bardrix::point3(-6, 6, -1);
    max2 = bardrix::point3(7, 14, 2);
    box2 = bardrix::bounding_box(min2, max2);

    box1 = bardrix::bounding_box(min1, max1);
    box1.merge(box2);
    EXPECT_EQ(box1.get_min(), bardrix::point3(-6, 3.4, -1));
    EXPECT_EQ(box1.get_max(), bardrix::point3(7, 14, 6.84));

    box1 = bardrix::bounding_box({ 1, 2, 3 }, { 3, 4, 5 });
    box2 = bardrix::bounding_box({ 1, 2, 3 }, { 3, 4, 5 });
    box1.merge(box2);
    EXPECT_EQ(box1.get_min(), bardrix::point3(1, 2, 3));
    EXPECT_EQ(box1.get_max(), bardrix::point3(3, 4, 5));

    box1 = bardrix::bounding_box({ 0, 0, 0 }, { 1, 2, 3 });
    box1.merge(bardrix::bounding_box({ 0, 0, 0 }, { 0, 0, 0 }));
    EXPECT_EQ(box1.get_min(), bardrix::point3(0, 0, 0));
    EXPECT_EQ(box1.get_max(), bardrix::point3(1, 2, 3));

    box1 = bardrix::bounding_box({ 0, 0, 0 }, { 0, 0, 0 });
    box1.merge(bardrix::bounding_box({ 0, 0, 0 }, { 0, 0, 0 }));
    EXPECT_EQ(box1.get_min(), bardrix::point3(0, 0, 0));
    EXPECT_EQ(box1.get_max(), bardrix::point3(0, 0, 0));
}

/// \brief Test the expand method of bounding_box
TEST(bounding_box, expand) {
    bardrix::point3 min = bardrix::point3(2, 3, 4);
    bardrix::point3 max = bardrix::point3(7, 6, 7);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    box.expand(1);
    EXPECT_EQ(box.get_min(), bardrix::point3(1, 2, 3));
    EXPECT_EQ(box.get_max(), bardrix::point3(8, 7, 8));

    box.expand(0.5);
    EXPECT_EQ(box.get_min(), bardrix::point3(0.5, 1.5, 2.5));
    EXPECT_EQ(box.get_max(), bardrix::point3(8.5, 7.5, 8.5));

    box.expand(-1);
    EXPECT_EQ(box.get_min(), bardrix::point3(1.5, 2.5, 3.5));
    EXPECT_EQ(box.get_max(), bardrix::point3(7.5, 6.5, 7.5));

    box.expand(-0.5);
    EXPECT_EQ(box.get_min(), bardrix::point3(2, 3, 4));
    EXPECT_EQ(box.get_max(), bardrix::point3(7, 6, 7));
}

/// \brief Test the expand method of bounding_box with edge cases
TEST(bounding_box, expand_edge_cases) {
    bardrix::point3 min = bardrix::point3(2, 3, 4);
    bardrix::point3 max = bardrix::point3(7, 6, 7);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    box.expand(0);
    EXPECT_EQ(box.get_min(), bardrix::point3(2, 3, 4));
    EXPECT_EQ(box.get_max(), bardrix::point3(7, 6, 7));

    box.expand(-10);
    EXPECT_EQ(box.get_min(), bardrix::point3(4.5, 4.5, 5.5));
    EXPECT_EQ(box.get_max(), bardrix::point3(4.5, 4.5, 5.5));
}

/// \brief Test the expanded method of bounding_box
TEST(bounding_box, expanded) {
    bardrix::point3 min = bardrix::point3(2, 3, 4);
    bardrix::point3 max = bardrix::point3(7, 6, 7);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    bardrix::bounding_box expanded = box.expanded(1);
    EXPECT_EQ(expanded.get_min(), bardrix::point3(1, 2, 3));
    EXPECT_EQ(expanded.get_max(), bardrix::point3(8, 7, 8));

    expanded = box.expanded(0.5);
    EXPECT_EQ(expanded.get_min(), bardrix::point3(1.5, 2.5, 3.5));
    EXPECT_EQ(expanded.get_max(), bardrix::point3(7.5, 6.5, 7.5));

    expanded = box.expanded(-1);
    EXPECT_EQ(expanded.get_min(), bardrix::point3(3, 4, 5));
    EXPECT_EQ(expanded.get_max(), bardrix::point3(6, 5, 6));

    expanded = box.expanded(-0.5);
    EXPECT_EQ(expanded.get_min(), bardrix::point3(2.5, 3.5, 4.5));
    EXPECT_EQ(expanded.get_max(), bardrix::point3(6.5, 5.5, 6.5));
}

/// \brief Test the expanded method of bounding_box with edge cases
TEST(bounding_box, expanded_edge_cases) {
    bardrix::point3 min = bardrix::point3(2, 3, 4);
    bardrix::point3 max = bardrix::point3(7, 6, 9);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    bardrix::bounding_box expanded = box.expanded(0);
    EXPECT_EQ(expanded.get_min(), bardrix::point3(2, 3, 4));
    EXPECT_EQ(expanded.get_max(), bardrix::point3(7, 6, 9));

    expanded = box.expanded(-10);
    EXPECT_EQ(expanded.get_min(), bardrix::point3(4.5, 4.5, 6.5));
    EXPECT_EQ(expanded.get_max(), bardrix::point3(4.5, 4.5, 6.5));

    expanded = box.expanded(-2);
    EXPECT_EQ(expanded.get_min(), bardrix::point3(4, 4.5, 6));
    EXPECT_EQ(expanded.get_max(), bardrix::point3(5, 4.5, 7));
}

/// \brief Test the is_empty method of bounding_box
TEST(bounding_box, is_empty) {
    bardrix::point3 min = bardrix::point3(2, 3, 4);
    bardrix::point3 max = bardrix::point3(7, 6, 7);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    EXPECT_FALSE(box.is_empty());

    box = bardrix::bounding_box({ 1, 2, 3 }, { 1, 2, 3 });
    EXPECT_TRUE(box.is_empty());

    box = bardrix::bounding_box({ 0, 0, 0 }, { 0, 0, 0 });
    EXPECT_TRUE(box.is_empty());

    box = bardrix::bounding_box({ 1, 2, 3 }, { 1, 2, 5 });
    EXPECT_FALSE(box.is_empty());

    box = bardrix::bounding_box({ 1, 2, 3 }, { 1, 4, 5 });
    EXPECT_FALSE(box.is_empty());

    box = bardrix::bounding_box({ 5, 3, 3 }, { 3, 4, 5 });
    EXPECT_FALSE(box.is_empty());
}

/// \brief Test the bounding_box intersects method with bounding_box
TEST(bounding_box, intersects_box) {
    bardrix::point3 min = bardrix::point3(2, 3, 4);
    bardrix::point3 max = bardrix::point3(7, 6, 7);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    EXPECT_TRUE(box.intersects(bardrix::bounding_box({ 1, 2, 3 }, { 3, 4, 5 }))); // Inside
    EXPECT_TRUE(box.intersects(bardrix::bounding_box({ 1, 2, 3 }, { 3, 4, 4 }))); // Inside
    EXPECT_TRUE(box.intersects(bardrix::bounding_box({ 1, 2, 3 }, { 3, 8, 10 }))); // Inside
    EXPECT_TRUE(box.intersects(bardrix::bounding_box({ 3, 4, 7 }, { 9, 7, 8 }))); // Inside
    EXPECT_TRUE(box.intersects(bardrix::bounding_box({ -2, -4, -7 }, { 9, 7, 8 }))); // Inside

    EXPECT_FALSE(box.intersects(bardrix::bounding_box({ 1, 2, 3 }, { 3, 2, 5 }))); // Outside
    EXPECT_FALSE(box.intersects(bardrix::bounding_box({ 1, 2, 3 }, { 3, 2, 5 }))); // Outside
    EXPECT_FALSE(box.intersects(bardrix::bounding_box({ 3, 7, 7 }, { 9, 7, 8 }))); // Outside
    EXPECT_FALSE(box.intersects(bardrix::bounding_box({ -2, -4, -7 }, { 9, -7, 8 }))); // Outside
}

/// \brief Test the bounding_box intersects method with bounding_box edge cases
TEST(bounding_box, intersects_box_edge_cases) {
    EXPECT_TRUE(bardrix::bounding_box({ 2, 3, 4 }, { 7, 6, 7 }).intersects(
            bardrix::bounding_box({ 2, 3, 4 }, { 7, 6, 7 }))); // Same box
    EXPECT_TRUE(bardrix::bounding_box({ -2, -3, 4 }, { 7, -6, -7 }).intersects(
            bardrix::bounding_box({ -2, -3, 4 }, { 7, -6, -7 }))); // Same box

    EXPECT_TRUE(bardrix::bounding_box({ 2, 3, 4 }, { 7, 6, 7 }).intersects(
            bardrix::bounding_box({ 2, 3, 4 }, { 7, 6, 5 }))); // No Depth
    EXPECT_TRUE(bardrix::bounding_box({ 2, 3, 4 }, { 7, 6, 7 }).intersects(
            bardrix::bounding_box({ 2, 3, 4 }, { 7, 4, 7 }))); // No Height
    EXPECT_TRUE(bardrix::bounding_box({ 2, 3, 4 }, { 7, 6, 7 }).intersects(
            bardrix::bounding_box({ 2, 3, 4 }, { 5, 6, 7 }))); // No Width
}

/// \brief Test the bounding_box intersects method with ray
TEST(bounding_box, intersects_ray) {
    bardrix::point3 min = bardrix::point3(-5.04, 3.4, 0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);
    double distance = 100;

    bardrix::ray ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(-1, 2, 2), distance);
    EXPECT_TRUE(box.intersects(ray));

    ray = bardrix::ray(bardrix::point3(2, 3, 1), bardrix::vector3(0, 0, 1), distance);
    EXPECT_TRUE(bardrix::bounding_box({ 1, 2, 3 }, { 3, 4, 5 }).intersects(ray));

    ray = bardrix::ray(bardrix::point3(0, 3, 4), bardrix::vector3(1, 0, 0), distance);
    EXPECT_TRUE(bardrix::bounding_box({ 1, 2, 3 }, { 3, 4, 5 }).intersects(ray));

    ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(-1.78419, 2.6324, 2), distance);
    EXPECT_TRUE(box.intersects(ray));

    ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(0.74519, 2.01385, 2), distance);
    EXPECT_TRUE(box.intersects(ray));

    ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(0.10442, 1.2, 1.73264), distance);
    EXPECT_TRUE(box.intersects(ray));

    ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(1.39641, 1.79423, 2), distance);
    EXPECT_TRUE(box.intersects(ray));

    ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(1.39641, 1.79423, 3.62911), distance);
    EXPECT_FALSE(box.intersects(ray));

    ray = bardrix::ray(bardrix::point3(-12, 4, 6), bardrix::vector3(0.10442, 1.016, 2), distance);
    EXPECT_FALSE(box.intersects(ray));
}

/// \brief Test the bounding_box intersects method with ray negative x, y, z directions
TEST(bounding_box, intersects_ray_negative_direction) {
    bardrix::point3 min = bardrix::point3(-5.04, 3.4, 0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);
    double distance = 100;

    bardrix::ray ray = bardrix::ray(bardrix::point3(2.7942, 6.20428, 7.47399),
                                    bardrix::vector3(-11.02986, 0.26419, -1.64038), distance);
    EXPECT_TRUE(box.intersects(ray));

    ray = bardrix::ray(bardrix::point3(2, 23, -4), bardrix::vector3(-1, -2, 0.7), distance);
    EXPECT_TRUE(box.intersects(ray));

    ray = bardrix::ray(bardrix::point3(-2.53588, 9.58673, -4), bardrix::vector3(-0.2, -0.1, 1), distance);
    EXPECT_TRUE(box.intersects(ray));

    ray = bardrix::ray(bardrix::point3(0, 20, 4), bardrix::vector3(-1, -2, -2), distance);
    EXPECT_FALSE(box.intersects(ray));

    ray = bardrix::ray(bardrix::point3(2, 23, -2), bardrix::vector3(9.64699, 2.19987, -1.64038), distance);
    EXPECT_FALSE(box.intersects(ray));

    ray = bardrix::ray(bardrix::point3(2, 23, -2), bardrix::vector3(-28.86337, -12.71138, 23.94488), distance);
    EXPECT_FALSE(box.intersects(ray));
}

/// \brief Test the bounding_box intersects method with distances of small values
TEST(bounding_box, intersects_ray_small_distance) {
    bardrix::point3 min = bardrix::point3(-5.04, 3.4, 0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    bardrix::ray ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(-1, 2, 2), 0.5);
    EXPECT_FALSE(box.intersects(ray));

    ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(-1.78419, 2.6324, 2), 1);
    EXPECT_FALSE(box.intersects(ray));

    ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(0.74519, 2.01385, 2), 0);
    EXPECT_FALSE(box.intersects(ray));
}

/// \brief Test the bounding_box intersects method where the ray is inside the box
TEST(bounding_box, intersects_ray_inside) {
    bardrix::point3 min = bardrix::point3(-5.04, 3.4, 0);
    bardrix::point3 max = bardrix::point3(4, 12.44, 6.84);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);
    double distance = 100;

    bardrix::ray ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(1, 2, 2), distance);
    EXPECT_TRUE(box.intersects(ray));
    ray = bardrix::ray(bardrix::point3(-5.04, 3.4, 0), bardrix::vector3(-1, -2, -2), distance);
    EXPECT_TRUE(box.intersects(ray));

    ray = bardrix::ray(box.center(), bardrix::vector3(1.78419, 2.6324, 2), distance);
    EXPECT_TRUE(box.intersects(ray));
    EXPECT_TRUE(box.inside(ray.position));
    ray.set_length(0);
    EXPECT_TRUE(box.inside(ray.position));

    box = bardrix::bounding_box({ 0, 0, 0 }, { 0, 0, 0 });
    ray.position = bardrix::point3(0, 0, 0);
    EXPECT_TRUE(box.intersects(ray));
}

/// \brief Test the bounding_box intersects method with edge cases
TEST(bounding_box, intersects_ray_edge_cases) {
    bardrix::point3 min = bardrix::point3(1, 1, 1);
    bardrix::point3 max = bardrix::point3(2, 2, 2);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);
    double distance = 100;

    bardrix::ray ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(1, 2, 1), distance);
    EXPECT_TRUE(box.intersects(ray));

    box.set_min_max(-max, -min);
    ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::vector3(1, 2, 1), distance);
    EXPECT_FALSE(box.intersects(ray));
}

///\brief Test the operator+ with a vector3
TEST(bounding_box, operator_plus_vector3) {
    bardrix::point3 min = bardrix::point3(-1, -1, -1);
    bardrix::point3 max = bardrix::point3(1, 1, 1);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    bardrix::vector3 vector = bardrix::vector3(1, 1, 1);
    bardrix::bounding_box new_box = box + vector;

    EXPECT_EQ(new_box.get_min(), bardrix::point3(0, 0, 0));
    EXPECT_EQ(new_box.get_max(), bardrix::point3(2, 2, 2));

    vector = bardrix::vector3(-1, -1, -1);
    new_box = box + vector;

    EXPECT_EQ(new_box.get_min(), bardrix::point3(-2, -2, -2));
    EXPECT_EQ(new_box.get_max(), bardrix::point3(0, 0, 0));

    vector = bardrix::vector3(0, 0, 0);
    new_box = box + vector;

    EXPECT_EQ(new_box.get_min(), bardrix::point3(-1, -1, -1));
    EXPECT_EQ(new_box.get_max(), bardrix::point3(1, 1, 1));
}

///\brief Test the operator+ with a value
TEST(bounding_box, operator_plus_value) {
    bardrix::point3 min = bardrix::point3(-1, -1, -1);
    bardrix::point3 max = bardrix::point3(1, 1, 1);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    bardrix::bounding_box new_box = box + 1;

    EXPECT_EQ(new_box.get_min(), bardrix::point3(0, 0, 0));
    EXPECT_EQ(new_box.get_max(), bardrix::point3(2, 2, 2));

    new_box = box + -1;

    EXPECT_EQ(new_box.get_min(), bardrix::point3(-2, -2, -2));
    EXPECT_EQ(new_box.get_max(), bardrix::point3(0, 0, 0));

    new_box = box + 0;

    EXPECT_EQ(new_box.get_min(), bardrix::point3(-1, -1, -1));
    EXPECT_EQ(new_box.get_max(), bardrix::point3(1, 1, 1));
}

///\brief Test the operator+= with a vector3
TEST(bounding_box, operator_plus_equal_vector3) {
    bardrix::point3 min = bardrix::point3(-1, -1, -1);
    bardrix::point3 max = bardrix::point3(1, 1, 1);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    bardrix::vector3 vector = bardrix::vector3(1, 1, 1);
    box += vector;

    EXPECT_EQ(box.get_min(), bardrix::point3(0, 0, 0));
    EXPECT_EQ(box.get_max(), bardrix::point3(2, 2, 2));

    vector = bardrix::vector3(-1, -1, -1);
    box = bardrix::bounding_box(min, max);
    box += vector;

    EXPECT_EQ(box.get_min(), bardrix::point3(-2, -2, -2));
    EXPECT_EQ(box.get_max(), bardrix::point3(0, 0, 0));

    vector = bardrix::vector3(0, 0, 0);
    box = bardrix::bounding_box(min, max);
    box += vector;

    EXPECT_EQ(box.get_min(), bardrix::point3(-1, -1, -1));
    EXPECT_EQ(box.get_max(), bardrix::point3(1, 1, 1));
}

///\brief Test the operator+= with a value
TEST(bounding_box, operator_plus_equal_value) {
    bardrix::point3 min = bardrix::point3(-1, -1, -1);
    bardrix::point3 max = bardrix::point3(1, 1, 1);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    box += 1;

    EXPECT_EQ(box.get_min(), bardrix::point3(0, 0, 0));
    EXPECT_EQ(box.get_max(), bardrix::point3(2, 2, 2));

    box = bardrix::bounding_box(min, max);
    box += -1;

    EXPECT_EQ(box.get_min(), bardrix::point3(-2, -2, -2));
    EXPECT_EQ(box.get_max(), bardrix::point3(0, 0, 0));

    box = bardrix::bounding_box(min, max);
    box += 0;

    EXPECT_EQ(box.get_min(), bardrix::point3(-1, -1, -1));
    EXPECT_EQ(box.get_max(), bardrix::point3(1, 1, 1));
}

///\brief Test the operator- with a vector3
TEST(bounding_box, operator_minus_vector3) {
    bardrix::point3 min = bardrix::point3(-1, -1, -1);
    bardrix::point3 max = bardrix::point3(1, 1, 1);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    bardrix::vector3 vector = bardrix::vector3(1, 1, 1);
    bardrix::bounding_box new_box = box - vector;

    EXPECT_EQ(new_box.get_min(), bardrix::point3(-2, -2, -2));
    EXPECT_EQ(new_box.get_max(), bardrix::point3(0, 0, 0));

    vector = bardrix::vector3(-1, -1, -1);
    new_box = box - vector;

    EXPECT_EQ(new_box.get_min(), bardrix::point3(0, 0, 0));
    EXPECT_EQ(new_box.get_max(), bardrix::point3(2, 2, 2));

    vector = bardrix::vector3(0, 0, 0);
    new_box = box - vector;

    EXPECT_EQ(new_box.get_min(), bardrix::point3(-1, -1, -1));
    EXPECT_EQ(new_box.get_max(), bardrix::point3(1, 1, 1));
}

///\brief Test the operator- with a value
TEST(bounding_box, operator_minus_value) {
    bardrix::point3 min = bardrix::point3(-1, -1, -1);
    bardrix::point3 max = bardrix::point3(1, 1, 1);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    bardrix::bounding_box new_box = box - 1;

    EXPECT_EQ(new_box.get_min(), bardrix::point3(-2, -2, -2));
    EXPECT_EQ(new_box.get_max(), bardrix::point3(0, 0, 0));

    new_box = box - -1;

    EXPECT_EQ(new_box.get_min(), bardrix::point3(0, 0, 0));
    EXPECT_EQ(new_box.get_max(), bardrix::point3(2, 2, 2));

    new_box = box - 0;

    EXPECT_EQ(new_box.get_min(), bardrix::point3(-1, -1, -1));
    EXPECT_EQ(new_box.get_max(), bardrix::point3(1, 1, 1));
}

///\brief Test the operator-= with a vector3
TEST(bounding_box, operator_minus_equal_vector3) {
    bardrix::point3 min = bardrix::point3(-1, -1, -1);
    bardrix::point3 max = bardrix::point3(1, 1, 1);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    bardrix::vector3 vector = bardrix::vector3(1, 1, 1);
    box -= vector;

    EXPECT_EQ(box.get_min(), bardrix::point3(-2, -2, -2));
    EXPECT_EQ(box.get_max(), bardrix::point3(0, 0, 0));

    vector = bardrix::vector3(-1, -1, -1);
    box = bardrix::bounding_box(min, max);
    box -= vector;

    EXPECT_EQ(box.get_min(), bardrix::point3(0, 0, 0));
    EXPECT_EQ(box.get_max(), bardrix::point3(2, 2, 2));

    vector = bardrix::vector3(0, 0, 0);
    box = bardrix::bounding_box(min, max);
    box -= vector;

    EXPECT_EQ(box.get_min(), bardrix::point3(-1, -1, -1));
    EXPECT_EQ(box.get_max(), bardrix::point3(1, 1, 1));
}

///\brief Test the operator-= with a value
TEST(bounding_box, operator_minus_equal_value) {
    bardrix::point3 min = bardrix::point3(-1, -1, -1);
    bardrix::point3 max = bardrix::point3(1, 1, 1);
    bardrix::bounding_box box = bardrix::bounding_box(min, max);

    box -= 1;

    EXPECT_EQ(box.get_min(), bardrix::point3(-2, -2, -2));
    EXPECT_EQ(box.get_max(), bardrix::point3(0, 0, 0));

    box = bardrix::bounding_box(min, max);
    box -= -1;

    EXPECT_EQ(box.get_min(), bardrix::point3(0, 0, 0));
    EXPECT_EQ(box.get_max(), bardrix::point3(2, 2, 2));

    box = bardrix::bounding_box(min, max);
    box -= 0;

    EXPECT_EQ(box.get_min(), bardrix::point3(-1, -1, -1));
    EXPECT_EQ(box.get_max(), bardrix::point3(1, 1, 1));
}

///\brief Test the operator== with two equal bounding boxes
TEST(bounding_box, operator_equal_equal) {
    bardrix::bounding_box box1 = bardrix::bounding_box({ 1, 2, 3 }, { 3, 4, 5 });
    bardrix::bounding_box box2 = bardrix::bounding_box({ 1, 2, 3 }, { 3, 4, 5 });
    EXPECT_TRUE(box1 == box2);

    box1 = bardrix::bounding_box({ 0, 0, 0 }, { 0, 0, 0 });
    box2 = bardrix::bounding_box({ 0, 0, 0 }, { 0, 0, 0 });
    EXPECT_TRUE(box1 == box2);

    box1 = bardrix::bounding_box({ -1, -1, -1 }, { 1, 1, 1 });
    box2 = bardrix::bounding_box({ -1, -1, -1 }, { 1, -1, 1 });
    EXPECT_FALSE(box1 == box2);
}

///\brief Test the operator!= with two equal bounding boxes
TEST(bounding_box, operator_not_equal) {
    bardrix::bounding_box box1 = bardrix::bounding_box({ 1, 2, 3 }, { 3, 4, 5 });
    bardrix::bounding_box box2 = bardrix::bounding_box({ 1, 2, 3 }, { 3, 4, 5 });
    EXPECT_FALSE(box1 != box2);

    box1 = bardrix::bounding_box({ 0, 0, 0 }, { 0, 0, 0 });
    box2 = bardrix::bounding_box({ 0, 0, 0 }, { 0, 0, 0 });
    EXPECT_FALSE(box1 != box2);

    box1 = bardrix::bounding_box({ -1, -1, -1 }, { 1, 1, 1 });
    box2 = bardrix::bounding_box({ -1, -1, -1 }, { 1, -1, 1 });
    EXPECT_TRUE(box1 != box2);
}

///\brief Test the operator<< with a bounding box
TEST(bounding_box, operator_stream) {
    bardrix::bounding_box box = bardrix::bounding_box({ 1, 2, 3 }, { 3, 4, 5 });
    std::stringstream stream;
    stream << box;
    EXPECT_EQ(stream.str(), "Bounding Box: (Min: (1, 2, 3), Max: (3, 4, 5))");
}

// SPHERE

/// \brief Test the constructor of sphere
TEST(sphere, constructor) {
    bardrix::sphere sphere = bardrix::sphere(4);
    EXPECT_EQ(sphere.get_position(), bardrix::point3(0, 0, 0));
    EXPECT_EQ(sphere.get_radius(), 4);
    EXPECT_EQ(sphere.get_material(), bardrix::material());

    sphere = bardrix::sphere();
    EXPECT_EQ(sphere.get_position(), bardrix::point3(0, 0, 0));
    EXPECT_EQ(sphere.get_radius(), 1);
    EXPECT_EQ(sphere.get_material(), bardrix::material());

    sphere = bardrix::sphere(bardrix::point3(1, 2, 3), 4);
    EXPECT_EQ(sphere.get_position(), bardrix::point3(1, 2, 3));
    EXPECT_EQ(sphere.get_radius(), 4);
    EXPECT_EQ(sphere.get_material(), bardrix::material());

    sphere = bardrix::sphere(bardrix::point3(-1, -2, -3), -5);
    EXPECT_EQ(sphere.get_position(), bardrix::point3(-1, -2, -3));
    EXPECT_EQ(sphere.get_radius(), 0);
    EXPECT_EQ(sphere.get_material(), bardrix::material());

    sphere = bardrix::sphere(bardrix::point3(0, 0, 0), bardrix::material(), 1);
    EXPECT_EQ(sphere.get_position(), bardrix::point3(0, 0, 0));
    EXPECT_EQ(sphere.get_radius(), 1);
    EXPECT_EQ(sphere.get_material(), bardrix::material());
}

/// \brief Test the set_radius method of sphere
TEST(sphere, set_radius) {
    bardrix::sphere sphere = bardrix::sphere();
    sphere.set_radius(4);
    EXPECT_EQ(sphere.get_radius(), 4);

    sphere.set_radius(0);
    EXPECT_EQ(sphere.get_radius(), 0);

    sphere.set_radius(-1);
    EXPECT_EQ(sphere.get_radius(), 0);
}

/// \brief Test the set_material method of sphere
TEST(sphere, set_material) {
    bardrix::sphere sphere = bardrix::sphere();
    bardrix::material material = bardrix::material();
    material.color = bardrix::color::red();
    sphere.set_material(material);
    EXPECT_EQ(sphere.get_material(), material);

    material.color = bardrix::color::green();
    sphere.set_material(material);
    EXPECT_EQ(sphere.get_material(), material);

    material.color = bardrix::color::blue();
    sphere.set_material(material);
    EXPECT_EQ(sphere.get_material(), material);
}

/// \brief Test the set_position method of sphere
TEST(sphere, set_position) {
    bardrix::sphere sphere = bardrix::sphere();
    sphere.set_position(bardrix::point3(1, 2, 3));
    EXPECT_EQ(sphere.get_position(), bardrix::point3(1, 2, 3));

    sphere.set_position(bardrix::point3(-1, -2, -3));
    EXPECT_EQ(sphere.get_position(), bardrix::point3(-1, -2, -3));

    sphere.set_position(bardrix::point3(0, 0, 0));
    EXPECT_EQ(sphere.get_position(), bardrix::point3(0, 0, 0));
}

/// \brief Test the intersects method of sphere with ray
TEST(sphere, intersects_ray) {
    bardrix::sphere sphere = bardrix::sphere(bardrix::point3(-12.72, 8.14, 0), 5);
    bardrix::sphere sphere_negative = bardrix::sphere(bardrix::point3(12.72, -8.14, 0), 5);

    bardrix::ray ray = bardrix::ray(bardrix::point3(5, 6, 7), bardrix::point3(-20.1, 10.55, 3));
    EXPECT_TRUE(sphere.intersection(ray).has_value());
    EXPECT_FALSE(sphere_negative.intersection(ray).has_value());
    EXPECT_EQ(sphere.intersection(ray).value(), bardrix::point3(-10.664, 8.83949, 4.50374));

    ray = bardrix::ray(bardrix::point3(5, 6, 7), bardrix::point3(-19.87738, 5.04547, 3));
    EXPECT_TRUE(sphere.intersection(ray).has_value());
    EXPECT_FALSE(sphere_negative.intersection(ray).has_value());
    EXPECT_EQ(sphere.intersection(ray).value(), bardrix::point3(-12.9181, 5.31249, 4.11898));

    ray = bardrix::ray(bardrix::point3(5, 6, 7), bardrix::point3(-19.87738, 5.04547, 3.67166));
    EXPECT_FALSE(sphere.intersection(ray).has_value());
    EXPECT_FALSE(sphere_negative.intersection(ray).has_value());
}

/// \brief Test the intersects method of sphere when the ray is inside the sphere
TEST(sphere, intersects_ray_inside) {
    bardrix::sphere sphere = bardrix::sphere(bardrix::point3(0, 0, 0), 5);

    bardrix::ray ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::point3(1, 1, 1));
    EXPECT_FALSE(sphere.intersection(ray).has_value());

    ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::point3(-1, -1, -1));
    EXPECT_FALSE(sphere.intersection(ray).has_value());

    ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::point3(0, 0, 0));
    EXPECT_FALSE(sphere.intersection(ray).has_value());

    ray = bardrix::ray(bardrix::point3(0, 0, 0), bardrix::point3(10, 20, 30));
    EXPECT_FALSE(sphere.intersection(ray).has_value());
}

/// \brief Test the normal_at method of sphere
TEST(sphere, normal_at) {
    bardrix::sphere sphere = bardrix::sphere(bardrix::point3(0, 0, 0), 5);

    EXPECT_EQ(sphere.normal_at({ 0, 0, 5 }), bardrix::vector3(0, 0, 1));
    EXPECT_EQ(sphere.normal_at({ 0, 0, -5 }), bardrix::vector3(0, 0, -1));
    EXPECT_EQ(sphere.normal_at({ 0, 5, 0 }), bardrix::vector3(0, 1, 0));
    EXPECT_EQ(sphere.normal_at({ 0, -5, 0 }), bardrix::vector3(0, -1, 0));
    EXPECT_EQ(sphere.normal_at({ 5, 0, 0 }), bardrix::vector3(1, 0, 0));
    EXPECT_EQ(sphere.normal_at({ -5, 0, 0 }), bardrix::vector3(-1, 0, 0));
}

/// \brief Test the normal_at method of sphere with edge cases
TEST(sphere, normal_at_edge_cases) {
    bardrix::sphere sphere = bardrix::sphere(bardrix::point3(0, 0, 0), 0);

    EXPECT_EQ(sphere.normal_at({ 0, 0, 0 }), bardrix::vector3(0, 0, 0));
    EXPECT_EQ(sphere.normal_at({ 0, 0, 1 }), bardrix::vector3(0, 0, 1));
    EXPECT_EQ(sphere.normal_at({ 0, 1, 0 }), bardrix::vector3(0, 1, 0));
    EXPECT_EQ(sphere.normal_at({ 1, 0, 0 }), bardrix::vector3(1, 0, 0));
}

/// \brief Test the bounding_box method of sphere
TEST(sphere, bounding_box) {
    bardrix::sphere sphere = bardrix::sphere(bardrix::point3(1, 2, 3), 4);
    bardrix::bounding_box box = sphere.bounding_box();

    EXPECT_EQ(box.get_min(), bardrix::point3(-3, -2, -1));
    EXPECT_EQ(box.get_max(), bardrix::point3(5, 6, 7));

    sphere = bardrix::sphere(bardrix::point3(-1, -2, -3), 5);
    box = sphere.bounding_box();

    EXPECT_EQ(box.get_min(), bardrix::point3(-6, -7, -8));
    EXPECT_EQ(box.get_max(), bardrix::point3(4, 3, 2));
}

/// \brief Test the bounding_box method of sphere with edge cases
TEST(sphere, bounding_box_edge_cases) {
    bardrix::sphere sphere = bardrix::sphere(bardrix::point3(0, 0, 0), 0);
    bardrix::bounding_box box = sphere.bounding_box();

    EXPECT_EQ(box.get_min(), bardrix::point3(0, 0, 0));
    EXPECT_EQ(box.get_max(), bardrix::point3(0, 0, 0));
}

/// \brief Test the operator== with two equal spheres
TEST(sphere, operator_equal_equal) {
    bardrix::sphere sphere1 = bardrix::sphere(bardrix::point3(1, 2, 3), 4);
    bardrix::sphere sphere2 = bardrix::sphere(bardrix::point3(1, 2, 3), 4);
    EXPECT_TRUE(sphere1 == sphere2);

    sphere1 = bardrix::sphere(bardrix::point3(0, 0, 0), 0);
    sphere2 = bardrix::sphere(bardrix::point3(0, 0, 0), 0);
    EXPECT_TRUE(sphere1 == sphere2);

    sphere1 = bardrix::sphere(bardrix::point3(-1, -2, -3), 5);
    sphere2 = bardrix::sphere(bardrix::point3(-1, -2, -3), 5);
    EXPECT_TRUE(sphere1 == sphere2);
}

/// \brief Test the operator!= with two equal spheres
TEST(sphere, operator_not_equal) {
    bardrix::sphere sphere1 = bardrix::sphere(bardrix::point3(1, 2, 3), 4);
    bardrix::sphere sphere2 = bardrix::sphere(bardrix::point3(1, 2, 3), 4);
    EXPECT_FALSE(sphere1 != sphere2);

    sphere1 = bardrix::sphere(bardrix::point3(0, 0, 0), 0);
    sphere2 = bardrix::sphere(bardrix::point3(0, 0, 0), 0);
    EXPECT_FALSE(sphere1 != sphere2);

    sphere1 = bardrix::sphere(bardrix::point3(-1, -2, -3), 5);
    sphere2 = bardrix::sphere(bardrix::point3(-1, -2, -3), 5);
    EXPECT_FALSE(sphere1 != sphere2);
}