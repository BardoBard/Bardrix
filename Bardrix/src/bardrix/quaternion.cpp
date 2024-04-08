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

    void quaternion::conjugate() noexcept {
        x = -x;
        y = -y;
        z = -z;
    }

    quaternion quaternion::conjugated() const noexcept {
        return {-x, -y, -z, w};
    }

    void quaternion::reciprocal() noexcept {
        double n = length();
        if (nearly_equal(n, 0)) return;

        conjugate();
        x /= n * n;
        y /= n * n;
        z /= n * n;
        w /= n * n;
    }

    quaternion quaternion::reciprocated() const noexcept {
        double n = length();
        if (nearly_equal(n, 0)) return *this;

        return {-x / (n * n), -y / (n * n), -z / (n * n), w / (n * n)};
    }

    double quaternion::length() const noexcept {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    void quaternion::normalize() noexcept {
        double n = length();
        if (nearly_equal(n, 0)) return;

        x /= n;
        y /= n;
        z /= n;
        w /= n;
    }

    quaternion quaternion::normalized() const noexcept {
        double n = length();
        if (nearly_equal(n, 0)) return *this;

        return {x / n, y / n, z / n, w / n};
    }

    quaternion quaternion::operator*(const quaternion& q) const noexcept {
        const double real = (x * q.x - y * q.y - z * q.z - w * q.w);
        const double i = (x * q.y + y * q.x + z * q.w - w * q.z);
        const double j = (x * q.z - y * q.w + z * q.x + w * q.y);
        const double k = (x * q.w + y * q.z - z * q.y + w * q.x);
        return {real, i, j, k};
    }

    std::ostream& quaternion::print(std::ostream& os) const {
        return os << "quaternion(" << x << ", " << y << ", " << z << ", " << w << ")";
    }

} // bardrix