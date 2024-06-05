//
// Created by Bardio on 04/06/2024.
//

#pragma once

#include <bardrix/bardrix.h>

namespace bardrix {

    /// \brief Mass, can be expressed in kg
    typedef double mass;

    /// \brief Time, can be expressed in s
    typedef double time;

    /// \brief Distance, can be expressed in m
    typedef double distance;

    /// \brief Velocity, can be expressed in m/s
    typedef double velocity;

    /// \brief Acceleration, can be expressed in m/s^2
    typedef double acceleration;

    /// \brief Force, can be expressed in N (kg*m/s^2)
    typedef double force;

    /// \brief The Universal Gravitational Constant (6.67430e-11 m^3 kg^-1 s^-2)
    /// \details This value can be changed if you want to simulate different gravity
    INLINE double universal_gravitational_constant = 6.67430e-11; // m^3 kg^-1 s^-2

    /// \brief Calculate the force using the formula F = m * a
    /// \param m Mass           (e.g. kg)
    /// \param a Acceleration   (e.g. m/s^2)
    /// \return Force           (e.g. N (kg*m/s^2))
    NODISCARD force calculate_force(mass m, acceleration a) noexcept;

    /// \brief Calculate the mass using the formula m = F / a
    /// \param f Force           (e.g. N (kg*m/s^2))
    /// \param a Acceleration    (e.g. m/s^2)
    /// \return Mass             (e.g. kg)
    NODISCARD mass calculate_mass(force f, acceleration a);

    /// \brief Calculate the acceleration using the formula a = F / m
    /// \param f Force           (e.g. N (kg*m/s^2))
    /// \param m Mass            (e.g. kg)
    /// \return Acceleration     (e.g. m/s^2)
    NODISCARD acceleration calculate_acceleration(force f, mass m);

    /// \brief Calculate the velocity using the formula v = a * t
    /// \param a Acceleration   (e.g. m/s^2)
    /// \param t Time            (e.g. s)
    /// \return Velocity         (e.g. m/s)
    NODISCARD velocity calculate_velocity(acceleration a, time t) noexcept;

    /// \brief Calculate the velocity using the formula v = F / m * t
    /// \param f Force           (e.g. N (kg*m/s^2))
    /// \param m Mass            (e.g. kg)
    /// \param t Time            (e.g. s)
    /// \return Velocity         (e.g. m/s)
    NODISCARD velocity calculate_velocity(force f, mass m, time t);

    /// \brief Calculate the distance using the formula d = v * t
    /// \param v Velocity        (e.g. m/s)
    /// \param t Time            (e.g. s)
    /// \return Distance         (e.g. m)
    NODISCARD distance calculate_distance(velocity v, time t) noexcept;

    /// \brief Calculate the Universal Gravitational Force using the formula F = G * (m1 * m2) / r^2
    /// \param m1 Mass object 1                                     (e.g. kg)
    /// \param m2 Mass object 2                                     (e.g. kg)
    /// \param d Distance between centroid of masses of the objects (e.g. m)
    /// \return Force exerted between the two objects               (e.g. N (kg*m/s^2))
    /// \details G is the Universal Gravitational Constant, change it for different gravity
    /// \note Isaac Newton's law of universal gravitation
    /// \see https://en.wikipedia.org/wiki/Newton%27s_law_of_universal_gravitation
    NODISCARD force calculate_gravity(mass m1, mass m2, distance d);

    /// \brief Calculate the escape velocity using the formula v = sqrt(2 * G * m / r)
    /// \param m Main body mass                                             (e.g. kg)
    /// \param r Distance from centroid to the object                       (e.g. m)
    /// \return The escape velocity                                         (e.g. m/s)
    /// \details The escape velocity is the minimum velocity needed for an object to escape the gravitational influence of a massive body
    /// \details G is the Universal Gravitational Constant, change it for different gravity
    /// \note The formula is v = sqrt(2 * G * m / r)
    NODISCARD velocity calculate_escape_velocity(mass m, distance r);

    /// \brief Calculate the orbital velocity using the formula v = sqrt(G * m / r)
    /// \param m Main body mass                                             (e.g. kg)
    /// \param d Distance from the centroid of the main body to the object  (e.g. m)
    /// \return The orbital velocity                                        (e.g. m/s)
    /// \details The orbital velocity is the velocity needed for an object to stay in orbit around a massive body
    /// \details G is the Universal Gravitational Constant, change it for different gravity
    /// \note The formula is v = sqrt(G * m / r)
    /// \example The orbital velocity of the Earth around the Sun is ~30 km/s
    NODISCARD velocity calculate_orbital_velocity(mass m, distance d);

} // namespace bardrix
