//
// Created by Bard on 14/03/2024.
//

#include <bardrix/vector3.h>

namespace bardrix {

    vector3::vector3(const double x, const double y, const double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double vector3::length() const noexcept {
        return std::sqrt(length_squared());
    }

    double vector3::length_squared() const noexcept {
        return x * x + y * y + z * z;
    }

    vector3 vector3::normalized() const noexcept {
        const double mag = length();

        if (nearly_equal(mag, 0))
            return *this;

        return {x / mag, y / mag, z / mag};
    }

    void vector3::normalize() noexcept {
        const double mag = length();

        if (nearly_equal(mag, 0))
            return;

        x /= mag;
        y /= mag;
        z /= mag;
    }

    double vector3::dot(const vector3& vec3) const noexcept {
        return x * vec3.x + y * vec3.y + z * vec3.z;
    }

    vector3 vector3::cross(const vector3& vec3) const noexcept {
        return {y * vec3.z - z * vec3.y, z * vec3.x - x * vec3.z, x * vec3.y - y * vec3.x};
    }

    double vector3::angle(const vector3& vec3) const {
        const double length_product = length() * vec3.length();

        if (nearly_equal(length_product, 0))
            return 1;

        return dot(vec3) / length_product;
    }

    std::ostream& vector3::print(std::ostream& os) const {
        return os << "(" << x << ", " << y << ", " << z << ")";
    }


} // namespace bardrix
