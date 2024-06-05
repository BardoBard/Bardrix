//
// Created by Bard on 04/04/2024.
//

#include <bardrix/quaternion.h>

namespace bardrix {

    quaternion::quaternion() noexcept: quaternion(0, 0, 0, 0) {}

    quaternion::quaternion(double x, double y, double z, double w) noexcept {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    quaternion& quaternion::conjugate() noexcept {
        x = -x;
        y = -y;
        z = -z;
        return *this;
    }

    quaternion quaternion::conjugated() const noexcept {
        return {-x, -y, -z, w};
    }

    quaternion& quaternion::reciprocal() noexcept {
        double n = length();
        if (nearly_equal(n, 0)) return *this;

        conjugate();
        x /= n * n;
        y /= n * n;
        z /= n * n;
        w /= n * n;
        return *this;
    }

    quaternion quaternion::reciprocated() const noexcept {
        double n = length();
        if (nearly_equal(n, 0)) return *this;

        return {-x / (n * n), -y / (n * n), -z / (n * n), w / (n * n)};
    }

    double quaternion::length() const noexcept {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    quaternion& quaternion::normalize() noexcept {
        double n = length();
        if (nearly_equal(n, 0)) return *this;

        x /= n;
        y /= n;
        z /= n;
        w /= n;
        return *this;
    }

    quaternion quaternion::normalized() const noexcept {
        double n = length();
        if (nearly_equal(n, 0)) return *this;

        return {x / n, y / n, z / n, w / n};
    }

    quaternion quaternion::operator*(const quaternion& q) const noexcept {
        return {
            w * q.x + x * q.w + y * q.z - z * q.y, // i
            w * q.y - x * q.z + y * q.w + z * q.x, // j
            w * q.z + x * q.y - y * q.x + z * q.w, // k
            w * q.w - x * q.x - y * q.y - z * q.z  // real
        };
    }

    std::ostream& quaternion::print(std::ostream& os) const {
        return os << "quaternion(" << x << "i, " << y << "j, " << z << "k, " << w << ")";
    }

} // bardrix