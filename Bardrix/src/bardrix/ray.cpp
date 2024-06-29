//
// Created by Bardio on 17/03/2024.
//

#include <bardrix/ray.h>

namespace bardrix {

    ray::ray(const vector3& direction) noexcept: ray(point3(), direction) {}

    ray::ray(const point3& position, const vector3& direction) noexcept: ray(position, direction, direction.length()) {}

    ray::ray(const point3& position, const point3& end) noexcept : ray((position), position.vector_to(end)) {}

    ray::ray(point3 position, const vector3& direction, double length) noexcept: position(std::move(position)),
                                                                                 direction_(direction.normalized()),
                                                                                 length_(length) {}

    const vector3& ray::get_direction() const noexcept { return direction_; }

    void ray::set_direction(const vector3& direction) noexcept { direction_ = direction.normalized(); }

    double ray::get_length() const noexcept { return length_; }

    void ray::set_length(double length) noexcept { length_ = (length < 0) ? 0 : length; }

    point3 ray::get_end() const noexcept { return point_at(length_); }

    point3 ray::point_at(const double distance) const noexcept {
        return (distance < 0)
               ? position
               : position + direction_ * distance;
    }

    std::ostream& ray::print(std::ostream& os) const {
        return os << "Position: " << position << ", Direction: " << direction_ << ", Length: " << length_;
    }

    std::ostream& operator<<(std::ostream& os, const ray& ray) { return ray.print(os); }

    bool ray::operator==(const ray& ray) const noexcept {
        return position == ray.position && direction_ == ray.direction_ && nearly_equal(length_, ray.length_);
    }

    bool ray::operator!=(const ray& ray) const noexcept { return !(*this == ray); }

} // namespace bardrix
