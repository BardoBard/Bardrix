//
// Created by Bard on 04/04/2024.
//

#pragma once

#include <bardrix/bardrix.h>
#include <bardrix/dimension4.h>
#include <bardrix/dimension3.h>
#include <bardrix/vector3.h>

namespace bardrix {

    /// \brief A quaternion class
    /// \details This class inherits from dimension4
    /// \note x, y and z are the imaginary parts and w is the real part
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
        /// \param x Initial imaginary i value
        /// \param y Initial imaginary j value
        /// \param z Initial imaginary k value
        /// \param w Initial real value
        quaternion(double x, double y, double z, double w) noexcept;

        /// \brief Calculates the conjugation of the quaternion
        /// \return A reference to this quaternion
        /// \details The conjugation of a quaternion is the same as the negation of the vector part of the quaternion
        /// \example quaternion(1, 2, 3, 4).conjugated() == quaternion(-1, -2, -3, 4)
        quaternion& conjugate() noexcept;

        /// \brief Calculates the conjugation of the quaternion
        /// \return The conjugated quaternion
        /// \details The conjugation of a quaternion is the same as the negation of the vector part of the quaternion
        /// \example quaternion(1, 2, 3, 4).conjugated() == quaternion(-1, -2, -3, 4)
        NODISCARD quaternion conjugated() const noexcept;

        /// \brief Calculates the reciprocal of this quaternion
        /// \return A reference to this quaternion
        /// \details The reciprocal of a quaternion is the conjugate of the quaternion divided by the length^2 of the quaternion
        /// \example quaternion(1, 2, 3, 4).reciprocal() == quaternion(-0.033, -0.066, -0.1, 0.13)
        quaternion& reciprocal() noexcept;

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
        /// \return A reference to this quaternion
        /// \details If the length of the quaternion is 0, it will not be normalized
        /// \example quaternion(1, 2, 3, 4).normalize() == quaternion(0.18, 0.37, 0.55, 0.73)
        quaternion& normalize() noexcept;

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
        /// \example quaternion(1, 2, 3, 4) * quaternion(5, 6, 7, 8) == quaternion(24, 48, 48, -6)
        NODISCARD quaternion operator*(const quaternion& q) const noexcept;

        /// \brief Rotates a 3D object around an axis by an angle in radians
        /// \tparam T The type of the point, e.g. point3, vector3, etc.
        /// \param dim3 The 3D object to rotate
        /// \param rotation_vector The axis to rotate around
        /// \param theta The angle in radians
        /// \return The rotated 3D object
        /// \details The rotation is done using quaternions
        /// \details If all the components of the given 3D object or rotation vector are 0, it will return the same 3D object (unmodified)
        /// \example quaternion::rotate_radians(point3(1, 2, 3), vector3(1, 0, 0), bardrix::pi) == point3(1, -2, -3)
        template<class T>
        NODISCARD static auto rotate_radians(const T& dim3, const vector3& rotation_vector,
                                             double theta) noexcept -> dimension3::enable_if_dimension3<T, T> {
            if (dim3 == 0 || rotation_vector == 0)
                return dim3;

            if (nearly_equal(theta, 0))
                return dim3;

            theta /= 2;

            //get cos and sin
            const double cos = std::cos(theta);
            const double sin = std::sin(theta);

            //get unitvector
            const vector3 unit_vector = rotation_vector.normalized() * sin;

            //quaternion
            const quaternion q = quaternion(unit_vector.x, unit_vector.y, unit_vector.z, cos);

            //conjugated quaternion of Q
            const quaternion con_q = q.conjugated();

            //quaternion from given point
            const quaternion p = quaternion(dim3.x, dim3.y, dim3.z, 0);

            const quaternion result = (con_q * p) * q;

            return {result.x, result.y, result.z};
        }

        /// \brief Rotates a 3D object around an axis by an angle in degrees
        /// \tparam T The type of the point, e.g. point3, vector3, etc.
        /// \param dim3 The 3D object to rotate
        /// \param rotation_vector The axis to rotate around
        /// \param theta The angle in degrees
        /// \return The rotated 3D object
        /// \details The rotation is done using quaternions
        /// \details If all the components of the given 3D object or rotation vector are 0, it will return the same 3D object (unmodified)
        /// \example quaternion::rotate_degrees(point3(1, 2, 3), vector3(1, 0, 0), 180) == point3(1, -2, -3)
        template<class T>
        NODISCARD static auto rotate_degrees(const T& dim3, const vector3& rotation_vector,
                                             double theta) noexcept -> dimension3::enable_if_dimension3<T, T> {
            return rotate_radians(dim3, rotation_vector, degrees_to_radians(theta));
        }

        /// \brief Mirrors a 3D object around an axis
        /// \tparam T The type of the point, e.g. point3, vector3, etc.
        /// \param dim3 The 3D object to mirror
        /// \param mirror_vector The axis to mirror around
        /// \return The mirrored 3D object
        /// \details The mirroring is done using quaternions
        /// \details If all the components of the given 3D object or rotation vector are 0, it will return the same 3D object (unmodified)
        /// \example quaternion::mirror(point3(1, 2, 3), vector3(1, 0, 0)) == point3(1, -2, -3)
        template<class T>
        NODISCARD static auto mirror(const T& dim3, const vector3& mirror_vector) noexcept -> dimension3::enable_if_dimension3<T, T> {
            if (dim3 == 0 || mirror_vector == 0)
                return dim3;

            //get unitvector (aka normalized vector)
            const vector3 unit_vector = mirror_vector.normalized();

            //quaternion
            const quaternion q = quaternion( unit_vector.x, unit_vector.y, unit_vector.z, 0);

            //conjugated quaternion of Q
            const quaternion con_q = q.conjugated();

            //quaternion from given point
            const quaternion p = quaternion(dim3.x, dim3.y, dim3.z, 0);

            const quaternion result = (con_q * p) * q;

            return {result.x, result.y, result.z};
        }

        /// \brief Print the quaternion to an output stream
        /// \param os The output stream
        /// \return The output stream
        /// \example std::cout << quaternion(1, 2, 3, 4) prints quaternion(1i, 2j, 3k, 4)
        std::ostream& print(std::ostream& os) const override;

    }; // quaternion

} // bardrix