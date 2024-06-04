//
// Created by Bardio on 04/06/2024.
//

#include <bardrix/physics.h>

/// \brief Test the force calculation using mass and acceleration
TEST(physics, force) {
    bardrix::mass m = 10.0; // kg
    bardrix::acceleration a = 2.0; // m/s^2
    bardrix::force f = bardrix::calculate_force(m, a); // N

    EXPECT_DOUBLE_EQ(f, 20.0);
}

/// \brief Test the mass calculation using force and acceleration
TEST(physics, mass) {
    bardrix::force f = 20.0; // N
    bardrix::acceleration a = 2.0; // m/s^2
    bardrix::mass m = bardrix::calculate_mass(f, a); // kg

    EXPECT_DOUBLE_EQ(m, 10.0);
}

/// \brief Test the degenerate case of mass calculation using force and zero acceleration
TEST(physics, mass_zero_acceleration) {
    bardrix::force f = 20.0; // N
    bardrix::acceleration a = 0.0; // m/s^2

    EXPECT_THROW(bardrix::calculate_mass(f, a), std::invalid_argument);
}

/// \brief Test the acceleration calculation using force and mass
TEST(physics, acceleration) {
    bardrix::force f = 20.0; // N
    bardrix::mass m = 10.0; // kg
    bardrix::acceleration a = bardrix::calculate_acceleration(f, m); // m/s^2

    EXPECT_DOUBLE_EQ(a, 2.0);
}

/// \brief Test the degenerate case of acceleration calculation using zero mass
TEST(physics, acceleration_zero_mass) {
    bardrix::force f = 20.0; // N
    bardrix::mass m = 0.0; //

    EXPECT_THROW(bardrix::calculate_acceleration(f, m), std::invalid_argument);
}

/// \brief Test the velocity calculation using acceleration and time
TEST(physics, velocity_a_t) {
    bardrix::acceleration a = 2.0; // m/s^2
    bardrix::time t = 5.0; // s
    bardrix::velocity v = bardrix::calculate_velocity(a, t); // m/s

    EXPECT_DOUBLE_EQ(v, 10.0);
}

/// \brief Test the velocity calculation using force, mass and time
TEST(physics, velocity_f_m_t) {
    bardrix::force f = 20.0; // N
    bardrix::mass m = 10.0; // kg
    bardrix::time t = 5.0; // s
    bardrix::velocity v = bardrix::calculate_velocity(f, m, t); // m/s

    EXPECT_DOUBLE_EQ(v, 10.0);
}

/// \brief Test the degenerate case of velocity calculation using zero mass and time
TEST(physics, velocity_zero_mass_time) {
    bardrix::force f = 20.0; // N
    bardrix::mass m = 0.0; //

    EXPECT_THROW(bardrix::calculate_velocity(f, m, 5.0), std::invalid_argument);

    m = 10.0;
    EXPECT_NO_THROW(bardrix::calculate_velocity(f, m, 0.0));
}

/// \brief Test the distance calculation using velocity and time
TEST(physics, distance) {
    bardrix::velocity v = 10.0; // m/s
    bardrix::time t = 5.0; // s
    bardrix::distance d = bardrix::calculate_distance(v, t); // m

    EXPECT_DOUBLE_EQ(d, 50.0);
}

/// \brief Test the gravitational force between the earth and the sun
TEST(physics, gravity) {
    bardrix::universal_gravitational_constant = 6.67430e-11; // m^3 kg^-1 s^-2
    bardrix::mass m_sun = 1.9884e30; // kg
    bardrix::mass m_earth = 5.9722e24; // kg

    // earth sun distance
    bardrix::distance d = 1.49597e11; // m
    bardrix::force f = bardrix::calculate_gravity(m_sun, m_earth, d); // N

    EXPECT_NEAR(f, 3.542e22, 1.0e20);

    // changing the gravitational constant
    bardrix::universal_gravitational_constant = 1.0;
    f = bardrix::calculate_gravity(m_sun, m_earth, d); // N

    EXPECT_NEAR(f, (m_sun * m_earth) / (d * d), 1.0e20);
}

/// \brief Test the gravitational force between the earth and the moon
TEST(physics, gravity_moon) {
    bardrix::universal_gravitational_constant = 6.67430e-11; // m^3 kg^-1 s^-2
    bardrix::mass m_earth = 5.9722e24; // kg
    bardrix::mass m_moon = 7.347e22; // kg

    // earth moon distance
    bardrix::distance d = 3.844e8; // m
    bardrix::force f = bardrix::calculate_gravity(m_earth, m_moon, d); // N

    EXPECT_NEAR(f, 1.982e20, 1.0e18);

    // changing the gravitational constant
    bardrix::universal_gravitational_constant = 1.0;
    f = bardrix::calculate_gravity(m_earth, m_moon, d); // N

    EXPECT_NEAR(f, (m_earth * m_moon) / (d * d), 1.0e18);
}

/// \brief Test the degenerate case of gravitational force calculation using zero distance
TEST(physics, gravity_zero_distance) {
    bardrix::mass m_sun = 1.9884e30; // kg
    bardrix::mass m_earth = 5.9722e24; // kg

    EXPECT_THROW(bardrix::calculate_gravity(m_sun, m_earth, 0.0), std::invalid_argument);
}

/// \brief Test the orbital velocity of the earth around the sun
TEST(physics, orbital_velocity) {
    bardrix::universal_gravitational_constant = 6.67430e-11; // m^3 kg^-1 s^-2
    bardrix::mass m_sun = 1.9884e30; // kg

    // earth sun distance
    bardrix::distance d = 1.496e11; // m
    bardrix::velocity v = bardrix::calculate_orbital_velocity(m_sun, d); // m/s

    EXPECT_NEAR(v, 29784.8, 1.0);

    // changing the gravitational constant
    bardrix::universal_gravitational_constant = 1.0;
    v = bardrix::calculate_orbital_velocity(m_sun, d); // m/s

    EXPECT_NEAR(v, std::sqrt(m_sun / d), 1.0);
}

/// \brief Test the degenerate case of orbital velocity calculation using zero distance
TEST(physics, orbital_velocity_zero_distance) {
    bardrix::mass m_sun = 1.9884e30; // kg

    EXPECT_THROW(bardrix::calculate_orbital_velocity(m_sun, 0.0), std::invalid_argument);
}

/// \brief Test the escape velocity of the earth
TEST(physics, escape_velocity) {
    bardrix::universal_gravitational_constant = 6.67430e-11; // m^3 kg^-1 s^-2
    bardrix::mass m_earth = 5.9722e24; // kg

    // earth radius
    bardrix::distance r = 6.371e6; // m
    bardrix::velocity v = bardrix::calculate_escape_velocity(m_earth, r); // m/s

    EXPECT_NEAR(v, 11186.0, 1.0);

    // changing the gravitational constant
    bardrix::universal_gravitational_constant = 1.0;
    v = bardrix::calculate_escape_velocity(m_earth, r); // m/s

    EXPECT_NEAR(v, std::sqrt(2 * m_earth / r), 1.0);
}
