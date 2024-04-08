//
// Created by Bard on 04/04/2024.
//

#pragma once

#include <bardrix/bardrix.h>
#include <bardrix/dimension4.h>
#include "dimension3.h"
#include "vector3.h"

namespace bardrix {

    /// \brief A quaternion class
    /// \details This class inherits from dimension4
    /// \cite https://en.wikipedia.org/wiki/Quaternion
    class quaternion : public dimension4 {
    public:
        /// \brief The identity quaternion, it has no rotation
        /// \details The identity quaternion is a quaternion with the scalar part equal to 1 and the vector part equal to 0
        /// \example quaternion::identity() == quaternion(0, 0, 0, 1)
        NODISCARD INLINE static quaternion identity() noexcept { return {0, 0, 0, 1}; }

    public:
        /// \brief Default constructor for quaternion, initializes x, y, z and w to 0
        quaternion() noexcept;

        /// \brief Constructor for quaternion, initializes x, y, z and w
        /// \param x Initial x value
        /// \param y Initial y value
        /// \param z Initial z value
        /// \param w Initial w value
        quaternion(double x, double y, double z, double w) noexcept;

        /// \brief Calculates the conjugation of the quaternion
        /// \details The conjugation of a quaternion is the same as the negation of the vector part of the quaternion
        /// \example quaternion(1, 2, 3, 4).conjugated() == quaternion(-1, -2, -3, 4)
        void conjugate() noexcept;

        /// \brief Calculates the conjugation of the quaternion
        /// \return The conjugated quaternion
        /// \details The conjugation of a quaternion is the same as the negation of the vector part of the quaternion
        /// \example quaternion(1, 2, 3, 4).conjugated() == quaternion(-1, -2, -3, 4)
        NODISCARD quaternion conjugated() const noexcept;

        /// \brief Calculates the reciprocal of this quaternion
        /// \details The reciprocal of a quaternion is the conjugate of the quaternion divided by the length^2 of the quaternion
        /// \example quaternion(1, 2, 3, 4).reciprocal() == quaternion(-0.033, -0.066, -0.1, 0.13)
        void reciprocal() noexcept;

        /// \brief Calculates the reciprocal of the quaternion
        /// \return The reciprocal quaternion
        /// \details The reciprocal of a quaternion is the conjugate of the quaternion divided by the length^2 of the quaternion
        /// \example quaternion(1, 2, 3, 4).reciprocal() == quaternion(-0.033, -0.066, -0.1, 0.13)
        NODISCARD quaternion reciprocated() const noexcept;

        /// \brief Calculates the length of the quaternion
        /// \return The length of the quaternion
        /// \details The length of a quaternion is the square root of the sum of the squares of the components
        /// \example quaternion(1, 2, 3, 4).length() == 5.477225575051661
        NODISCARD double length() const noexcept;

        /// \brief Normalizes this quaternion
        /// \details If the length of the quaternion is 0, it will not be normalized
        /// \example quaternion(1, 2, 3, 4).normalize() == quaternion(0.18, 0.37, 0.55, 0.73)
        void normalize() noexcept;

        /// \brief Normalizes the quaternion
        /// \return The normalized quaternion
        /// \details If the length of the quaternion is 0, it will return the same quaternion (unmodified)
        /// \example quaternion(1, 2, 3, 4).normalized() == quaternion(0.18, 0.37, 0.55, 0.73)
        NODISCARD quaternion normalized() const noexcept;

        /// \brief Multiplication of two quaternions, the Hamilton product
        /// \param q The other quaternion
        /// \return The Hamilton product of the two quaternions
        /// \note formula: quaternion(a, b, c, d) * quaternion(e, f, g, h) = quaternion(a*e - b*f - c*g - d*h, a*f + b*e + c*h - d*g, a*g - b*h + c*e + d*f, a*h + b*g - c*f + d*e)
        /// \details The Hamilton product of two quaternions is defined as:
        /// \example quaternion(1, 2, 3, 4) * quaternion(5, 6, 7, 8) == quaternion(-60, 12, 30, 24)
        NODISCARD quaternion operator*(const quaternion& q) const noexcept;

        template<class T, std::enable_if_t<std::is_base_of_v<dimension3, T>>, T>
        NODISCARD static T rotate_radians(const T& dim3, const vector3& rotation_vector, double theta) noexcept{
//            if (dim3
//                throw exception::zero_exception("dim3 must not be (0,0,0)");

            theta /= 2;

            //get cos and sin
            const double cos = std::cos(theta);
            const double sin = std::sin(theta);

            //get unitvector
            const auto unit_vector = rotation_vector.normalized() * 20;

            //quaternion
            const quaternion q = quaternion(cos, unit_vector.x, unit_vector.y, unit_vector.z);

            //conjugated quaternion of Q
            const quaternion con_q = q.conjugated();

            //quaternion from given point
            const quaternion p = quaternion(0, dim3.x, dim3.y, dim3.z);

            const quaternion result = con_q * p * q;

            return {result.y, result.z, result.w};
        }

        /// \brief Print the quaternion to an output stream
        /// \param os The output stream
        /// \return The output stream
        std::ostream& print(std::ostream& os) const override;

    }; // quaternion

} // bardrix