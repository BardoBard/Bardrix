//
// Created by Bardio on 04/06/2024.
//

#include <bardrix/physics.h>

namespace bardrix {

    force calculate_force(mass m, acceleration a) noexcept { return m * a; }

    mass calculate_mass(force f, acceleration a) {
        if (nearly_equal(a, 0)) UNLIKELY throw std::invalid_argument("Acceleration cannot be zero.");
        return f / a;
    }

    acceleration calculate_acceleration(force f, mass m) {
        if (nearly_equal(m, 0)) UNLIKELY throw std::invalid_argument("Mass cannot be zero.");
        return f / m;
    }

    velocity calculate_velocity(acceleration a, time t) noexcept { return a * t; }

    velocity calculate_velocity(force f, mass m, time t) {
        if (nearly_equal(m, 0)) UNLIKELY throw std::invalid_argument("Mass cannot be zero.");
        return f / m * t;
    }

    distance calculate_distance(velocity v, time t) noexcept { return v * t; }

    force calculate_gravity(mass m1, mass m2, distance d) {
        if (nearly_equal(d, 0)) UNLIKELY throw std::invalid_argument("Distance cannot be zero.");
        return universal_gravitational_constant * (m1 * m2) / (d * d);
    }

    velocity calculate_escape_velocity(mass m, distance r) {
        if (nearly_equal(r, 0)) UNLIKELY throw std::invalid_argument("Radius cannot be zero.");
        return std::sqrt(2 * universal_gravitational_constant * m / r);
    }

    velocity calculate_orbital_velocity(mass m, distance d) {
        if (nearly_equal(d, 0)) UNLIKELY throw std::invalid_argument("Distance cannot be zero.");
        return std::sqrt(universal_gravitational_constant * m / d);
    }

} // namespace bardrix
