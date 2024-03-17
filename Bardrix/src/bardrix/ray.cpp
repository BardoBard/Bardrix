//
// Created by Bardio on 17/03/2024.
//

#include <bardrix/ray.h>

namespace bardrix {

    ray::ray() : ray(point3(), vector3(0, 0, 1), 1) {}

    ray::ray(const point3& origin, const vector3& direction) : ray(origin, direction, direction.length()) {}

    ray::ray(point3 origin, const vector3& direction, double length) : origin_(std::move(origin)),
                                                                       direction_(direction.normalize()),
                                                                       length_(length) {}

    const point3& ray::get_origin() const noexcept { return origin_; };

    const vector3& ray::get_direction() const noexcept { return direction_; }

    double ray::get_length() const noexcept { return length_; }

    point3 ray::point_at(const double distance) const noexcept { return origin_ + direction_ * distance; }

    point3 ray::end() const noexcept { return point_at(length_); }

    std::ostream& ray::print(std::ostream& os) const {
        return os << "Origin: " << origin_ << ", Direction: " << direction_ << ", Length: " << length_;
    }

} // namespace bardrix
