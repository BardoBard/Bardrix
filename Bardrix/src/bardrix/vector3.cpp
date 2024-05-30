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

        return { x / mag, y / mag, z / mag };
    }

    vector3& vector3::normalize() noexcept {
        const double mag = length();

        if (nearly_equal(mag, 0))
            return *this;

        x /= mag;
        y /= mag;
        z /= mag;

        return *this;
    }

    double vector3::dot(const vector3& vec3) const noexcept {
        return x * vec3.x + y * vec3.y + z * vec3.z;
    }

    vector3 vector3::cross(const vector3& vec3) const noexcept {
        return { y * vec3.z - z * vec3.y, z * vec3.x - x * vec3.z, x * vec3.y - y * vec3.x };
    }

    double vector3::angle(const vector3& vec3) const {
        const double length_product = length() * vec3.length();

        if (nearly_equal(length_product, 0))
            return 1;

        return dot(vec3) / length_product;
    }

    std::optional<vector3> vector3::reflection(const vector3& normal) const {
        // Cannot reflect a vector with length 0 or a normal with length 0
        if (*this == 0 || normal == 0)
            return std::nullopt;

        const vector3 normalized_normal = normal.normalized();
        const double dot = this->dot(normalized_normal);

        // Dot < 0 means the vector is behind the normal
        // We're unable to reflect a vector that is behind the normal
        if (dot < 0)
            return std::nullopt;

        return normalized_normal * 2 * dot - *this;
    }

    std::optional<vector3> vector3::refraction(const vector3& normal, double refractive_ratio) const {
        return refraction(normal, refractive_ratio, 1);
    }

    std::optional<vector3> vector3::refraction(const vector3& normal, const double medium1, const double medium2) const {
        if (*this == 0 || normal == 0)
            return std::nullopt;

        // Cannot devide by 0
        if (nearly_equal(medium2, 0))
            return std::nullopt;

        const double ratio = medium1 / medium2;

        // If the ratio is less than or equal to 0, it means the light is going from a denser medium to a less dense medium
        if (less_than_or_nearly_equal(ratio, 0))
            return std::nullopt;

        const vector3 normalized_normal = normal.normalized();
        const vector3 normalized_vector = this->normalized();

        const double cos_theta1 = -normalized_normal.dot(normalized_vector);
        const double sin_theta2_squared = ratio * ratio * (1.0 - cos_theta1 * cos_theta1);

        // Internal reflection occurs when sin_theta2_squared > 1
        if (sin_theta2_squared > 1.0)
            return std::nullopt;

        return (normalized_vector * ratio + normalized_normal *
                                            (ratio * cos_theta1 - std::sqrt(1.0 - sin_theta2_squared)));
    }

    std::ostream& vector3::print(std::ostream& os) const {
        return os << "(" << x << ", " << y << ", " << z << ")";
    }

} // namespace bardrix
