//
// Created by Bardio on 22/05/2024.
//

#include "sphere.h"

sphere::sphere(double radius) : sphere(radius, bardrix::point3(0, 0, 0)) {}

sphere::sphere(double radius, const bardrix::point3& position) : radius_(radius), position(position) {}

void sphere::set_material(const bardrix::material& material) { this->material_ = material; }

const bardrix::material& sphere::get_material() const { return material_; }

void sphere::set_position(const bardrix::point3& position) { this->position = position; }

const bardrix::point3& sphere::get_position() const { return position; }

bardrix::vector3 sphere::normal_at(const bardrix::point3& point) const {
    return position.vector_to(point).normalized();
}

std::optional <bardrix::point3> sphere::intersection(const bardrix::ray& ray) const {

    // Basic hit function for a sphere

    bardrix::vector3 direction = ray.get_direction();

    // Gets vector from points: ray origin and sphere center
    bardrix::vector3 oc_vec = ray.position.vector_to(position);

    // Get dot product of origin-center-Vector and normalizedDirection
    double t = oc_vec.dot(direction);

    // Turn unit vector direction into a vector direction
    direction = direction * t;

    // Length from ray origin to sphere center
    oc_vec = direction - oc_vec;

    // |q|^2
    const double p2 = oc_vec.dot(oc_vec);

    // Radius^2
    const double r2 = radius_ * radius_;

    if (p2 > r2)
        return std::nullopt; //a smart way to check if ray intersects before taking the sqrt

    // Calculate distance to intersection
    t -= std::sqrt(r2 - p2);

    // If we intersect sphere return the length
    return (t < ray.get_length() && t > 0)
           ? std::optional(position + direction * t)
           : std::nullopt;
}

