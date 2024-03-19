//
// Created by Bard on 14/03/2024.
//

#include <bardrix/point3.h>

namespace bardrix {

    point3::point3(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double point3::distance(const point3& point3) const noexcept {
        return std::sqrt(distance_squared(point3));
    }

    double point3::distance_squared(const point3& point3) const noexcept {
        double dx = point3.x - x;
        double dy = point3.y - y;
        double dz = point3.z - z;
        return dx * dx + dy * dy + dz * dz;
    }

    point3 point3::midpoint(const point3& point3) const noexcept {
        return { (x + point3.x) / 2, (y + point3.y) / 2, (z + point3.z) / 2 };
    }

    vector3 point3::vector_to(const point3& point3) const noexcept {
        return { point3.x - x, point3.y - y, point3.z - z };
    }

    point3 point3::operator+(const vector3& vector3) const noexcept {
        point3 copy = *this;
        copy.x += vector3.x;
        copy.y += vector3.y;
        copy.z += vector3.z;
        return copy;
    }

    point3 point3::operator-(const vector3& vector3) const noexcept {
        point3 copy = *this;
        copy.x -= vector3.x;
        copy.y -= vector3.y;
        copy.z -= vector3.z;
        return copy;
    }

    std::ostream& point3::print(std::ostream& os) const {
        return os << "(" << x << ", " << y << ", " << z << ")";
    }


} // namespace bardrix