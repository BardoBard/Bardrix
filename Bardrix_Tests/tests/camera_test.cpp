//
// Created by Bard on 20/03/2024.
//

#include <bardrix/camera.h>

/// \brief Test the default constructor
TEST(camera, constructor) {
    bardrix::camera camera = bardrix::camera(bardrix::point3{0, 0, 0}, bardrix::vector3{0, 0, 0});

    EXPECT_EQ(camera.position, bardrix::point3(0, 0, 0));
    EXPECT_EQ(camera.get_direction(), bardrix::vector3(0, 0, 1)); // Default direction
    EXPECT_EQ(camera.get_fov(), 90);
    EXPECT_EQ(camera.get_width(), 800);
    EXPECT_EQ(camera.get_height(), 600);
}

/// \brief Test the constructor with values
TEST(camera, constructor_with_values) {
    bardrix::camera camera = bardrix::camera(bardrix::point3{1, 2, 3}, bardrix::vector3{4, 5, 6}, 360, 240, 45);

    EXPECT_EQ(camera.position, bardrix::point3(1, 2, 3));
    EXPECT_EQ(camera.get_direction(), bardrix::vector3(4, 5, 6).normalized());
    EXPECT_EQ(camera.get_fov(), 45);
    EXPECT_EQ(camera.get_width(), 360);
    EXPECT_EQ(camera.get_height(), 240);
}

TEST(camera, constructor_with_values_2) {
    bardrix::camera camera = bardrix::camera(bardrix::point3{1, 2, 3}, bardrix::vector3{4, 5, 6}, 360);

    EXPECT_EQ(camera.position, bardrix::point3(1, 2, 3));
    EXPECT_EQ(camera.get_direction(), bardrix::vector3(4, 5, 6).normalized());
    EXPECT_EQ(camera.get_fov(), 90);
    EXPECT_EQ(camera.get_width(), 360);
    EXPECT_EQ(camera.get_height(), 360);
}

/// \brief Test the constructor with degenerate values
TEST(camera, constructor_degenerate) {
    bardrix::camera camera = bardrix::camera(bardrix::point3{0, 0, 0}, bardrix::vector3{0, 0, 0}, 0, 0, 0);

    EXPECT_EQ(camera.position, bardrix::point3(0, 0, 0));
    EXPECT_EQ(camera.get_direction(), bardrix::vector3(0, 0, 1)); // Default direction
    EXPECT_EQ(camera.get_fov(), 0);
    EXPECT_EQ(camera.get_width(), 0);
    EXPECT_EQ(camera.get_height(), 0);

    camera = bardrix::camera(bardrix::point3{1, 2, 3}, bardrix::vector3{-20, 0, 0}, 425, 2423, 180);

    EXPECT_EQ(camera.position, bardrix::point3(1, 2, 3));
    EXPECT_EQ(camera.get_direction(), bardrix::vector3(-20, 0, 0).normalized());
    EXPECT_EQ(camera.get_fov(), 179);
    EXPECT_EQ(camera.get_width(), 425);
    EXPECT_EQ(camera.get_height(), 2423);
}

/// \brief Test the set_direction method
TEST(camera, set_direction) {
    bardrix::camera camera = bardrix::camera(bardrix::point3{0, 0, 0}, bardrix::vector3{0, 0, 0});

    camera.set_direction(bardrix::vector3{1, 2, 3});
    EXPECT_EQ(camera.get_direction(), bardrix::vector3(1, 2, 3).normalized());

    camera.set_direction(bardrix::vector3{0, 0, 0});
    EXPECT_EQ(camera.get_direction(), bardrix::vector3(0, 0, 1)); // Default direction
}

/// \brief Test the set_fov method
TEST(camera, set_fov) {
    bardrix::camera camera = bardrix::camera(bardrix::point3{0, 0, 0}, bardrix::vector3{0, 0, 0});

    camera.set_fov(45);
    EXPECT_EQ(camera.get_fov(), 45);

    camera.set_fov(180);
    EXPECT_EQ(camera.get_fov(), 179);
}


/// \brief Test the set_width method
TEST(camera, set_width) {
    bardrix::camera camera = bardrix::camera(bardrix::point3{0, 0, 0}, bardrix::vector3{0, 0, 0});

    camera.set_width(800);
    EXPECT_EQ(camera.get_width(), 800);

    camera.set_width(-1);
    EXPECT_EQ(camera.get_width(), 0);
}

/// \brief Test the set_height method
TEST(camera, set_height) {
    bardrix::camera camera = bardrix::camera(bardrix::point3{0, 0, 0}, bardrix::vector3{0, 0, 0});

    camera.set_height(600);
    EXPECT_EQ(camera.get_height(), 600);

    camera.set_height(-1);
    EXPECT_EQ(camera.get_height(), 0);
}

/// \brief Test the shoot_ray method
TEST(camera, shoot_ray) {
    bardrix::camera camera = bardrix::camera(bardrix::point3{0, 0, 0}, bardrix::vector3{0, 0, 0}, 800, 600, 90);

    std::optional<bardrix::ray> ray = camera.shoot_ray(0, 0, 1);
    EXPECT_TRUE(ray.has_value());
    EXPECT_EQ(ray.value().position, bardrix::point3(0, 0, 0));
    EXPECT_EQ(ray.value().get_direction(), bardrix::vector3(1, 1, 1).normalized());
    EXPECT_DOUBLE_EQ(ray.value().get_length(), 1);
}

/// \brief Test the shoot_ray method
TEST(camera, shoot_ray_2) {

    // Setup
    unsigned int screen_size = 100;
    bardrix::point3 position = bardrix::point3{-1, 2, 0};
    bardrix::vector3 direction = bardrix::vector3{9, 65, 24}.normalized();
    double distance = 7;

    // Execution
    bardrix::camera camera = bardrix::camera(position, direction, screen_size, screen_size, 120);

    // Rays
    std::optional<bardrix::ray> ray = camera.shoot_ray(screen_size / 2, screen_size / 2, distance);
    std::optional<bardrix::ray> ray2 = camera.shoot_ray(63, 65, 73);

    // Expected
    bardrix::ray ray2_expected = bardrix::ray(position, bardrix::vector3(-0.261844, 0.66309, 0.701249), 73);

    EXPECT_TRUE(ray.has_value());
    EXPECT_TRUE(ray2.has_value());

    EXPECT_EQ(ray.value(), bardrix::ray(position, direction, distance));
    EXPECT_EQ(ray2.value(), ray2_expected);
}

/// \brief Test the shoot_ray method
TEST(camera, shoot_ray_3) {

    // Setup
    unsigned int screen_size = 342;
    bardrix::point3 position = bardrix::point3{53, 42, -1};
    bardrix::vector3 direction = bardrix::vector3{1, 0, 0}.normalized();
    double distance = 7;

    // Execution
    bardrix::camera camera = bardrix::camera(position, direction, screen_size, screen_size, 23);

    // Rays
    std::optional<bardrix::ray> ray = camera.shoot_ray(0, 0, distance);
    std::optional<bardrix::ray> ray2 = camera.shoot_ray(100, 100, distance);

    // Expected
    bardrix::ray ray_expected = bardrix::ray(position, bardrix::vector3(0.961012, 0.19552, 0.19552), distance);
    bardrix::ray ray2_expected = bardrix::ray(position, bardrix::vector3(0.99294, 0.0838779, 0.0838779), distance);

    EXPECT_TRUE(ray.has_value());
    EXPECT_TRUE(ray2.has_value());

    EXPECT_EQ(ray.value(), ray_expected);
    EXPECT_EQ(ray2.value(), ray2_expected);
}

/// \brief Test shoot_ray with x or y greater than or equal to the width or height
TEST(camera, shoot_ray_degenerate) {
    bardrix::camera camera = bardrix::camera(bardrix::point3{0, 0, 0}, bardrix::vector3{0, 0, 0}, 800, 600, 90);

    std::optional<bardrix::ray> ray = camera.shoot_ray(800, 600, 1);
    EXPECT_FALSE(ray.has_value());

    ray = camera.shoot_ray(0, 600, 1);
    EXPECT_FALSE(ray.has_value());

    ray = camera.shoot_ray(800, 0, 1);
    EXPECT_FALSE(ray.has_value());

    ray = camera.shoot_ray(0, 0, 1);
    EXPECT_TRUE(ray.has_value());

    camera.set_width(0);

    ray = camera.shoot_ray(0, 0, 1);
    EXPECT_FALSE(ray.has_value());

    camera.set_width(800);
    camera.set_height(0);

    ray = camera.shoot_ray(0, 0, 1);
    EXPECT_FALSE(ray.has_value());

    camera.set_height(600);
    camera.set_fov(0);

    ray = camera.shoot_ray(0, 0, 1);
    EXPECT_TRUE(ray.has_value());

    camera.set_fov(90);
    ray = camera.shoot_ray(-1, 0, 1);
    EXPECT_FALSE(ray.has_value());

    ray = camera.shoot_ray(0, -1, 1);
    EXPECT_FALSE(ray.has_value());
}

/// \brief Test the look_at method
TEST(camera, look_at) {
    bardrix::camera camera = bardrix::camera(bardrix::point3{0, 0, 0}, bardrix::vector3{0, 0, 0});

    camera.look_at(bardrix::point3{1, 2, 3});
    EXPECT_EQ(camera.get_direction(), bardrix::vector3(1, 2, 3).normalized());

    camera.look_at(bardrix::point3{-2, 35, 1});
    EXPECT_EQ(camera.get_direction(), bardrix::vector3(-2, 35, 1).normalized());
}

/// \brief Test the look_at method with the same point
TEST(camera, look_at_degenerate) {
    bardrix::camera camera = bardrix::camera(bardrix::point3{0, 0, 0}, bardrix::vector3{0, 0, 0});

    camera.look_at(bardrix::point3{0, 0, 0});
    EXPECT_EQ(camera.get_direction(), bardrix::vector3(0, 0, 1));
}