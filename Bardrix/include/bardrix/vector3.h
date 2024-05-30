//
// Created by Bard on 14/03/2024.
//

#pragma once

#include <bardrix/bardrix.h>
#include <bardrix/dimension3.h>

namespace bardrix {

    /// \brief A 3D vector class
    /// \details This class inherits from dimension3
    class vector3 : public dimension3 {

    public:
        /// \brief Default constructor for vector3, initializes x, y and z to 0
        vector3() noexcept = default;

        /// \brief Constructor for vector3, initializes x, y and z
        /// \param x Initial x value
        /// \param y Initial y value
        /// \param z Initial z value
        vector3(double x, double y, double z);

        /// \brief Magnitude of the vector, the length of the vector
        /// \return The length of the vector
        NODISCARD double length() const noexcept;

        /// \brief Magnitude of the vector squared, the length of the vector squared
        /// \return The length of the vector squared
        NODISCARD double length_squared() const noexcept;

        /// \brief Normalizes this vector, making it a unit vector
        /// \return A reference to this vector
        /// \details If the length of the vector is 0, it will not be normalized
        /// \example vector3(0, 0, 0).normalize() == vector3(0, 0, 0)
        /// \example vector3(1, 2, 3).normalize() == vector3(0.267, 0.534, 0.802)
        vector3& normalize() noexcept;

        /// \brief Normalize the vector, making it a unit vector
        /// \return The normalized vector
        /// \details If the length of the vector is 0, it will not be normalized
        /// \example vector3(0, 0, 0).normalize() == vector3(0, 0, 0)
        /// \example vector3(1, 2, 3).normalize() == vector3(0.267, 0.534, 0.802)
        NODISCARD vector3 normalized() const noexcept;

        /// \brief Dot product of two vectors
        /// \param vec3 The other vector
        /// \return The dot product of the two vectors
        NODISCARD double dot(const vector3& vec3) const noexcept;

        /// \brief Cross product of two vectors
        /// \param vec3 The other vector
        /// \return The cross product of the two vectors
        NODISCARD vector3 cross(const vector3& vec3) const noexcept;

        /// \brief Angle between two vectors [-1, 1]
        /// \param vec3 The other vector
        /// \note When the angle is 1, the vectors are parallel, when the angle is -1, the vectors are opposite
        /// \details This vector and the other vector will normalized before calculating the angle
        /// \details If the length of any of the vectors is 0, it will return 1, aka orthogonal
        /// \return The angle between the two vectors [-1, 1]
        NODISCARD double angle(const vector3& vec3) const;

        /// \brief Calculates the reflection of this vector onto a normal
        ///        The result will be an outgoing vector with the same length as the incoming vector
        /// \param normal The normal vector, will be normalized for you
        /// \note If the incoming vector or the normal vector has length 0, it will return std::nullopt
        /// \note If the incoming vector is behind the normal, it will return std::nullopt
        /// \return reflection of this vector on a normalized normal, if a degenerate case is found, it will return std::nullopt
        /// \details formula: r = n (2 * (d . n)) − d
        /// \details r is the reflection
        /// \details n is the normal (normalized)
        /// \details d is the vector
        /// \see https://math.stackexchange.com/a/4019883
        /// \see bardrix::quaternion::mirror for the same functionality
        NODISCARD std::optional<vector3> reflection(const vector3& normal) const;

        /// \brief Calculates the refraction of this vector through a normal
        ///        The result will be an outgoing normalized vector
        /// \param normal The normal vector, will be normalized for you
        /// \param refractive_ratio The refractive index ratio of the two mediums, like air and water
        /// \return The refracted vector, if any degenerate case is found, it will return std::nullopt
        /// \note The vector and normal vector must have a length greater than zero
        /// \note The refractive index ratio must be greater than zero
        /// \note There mustn't be total internal reflection
        /// \see https://en.wikipedia.org/wiki/Refractive_index
        /// \see https://en.wikipedia.org/wiki/Snell%27s_law#Vector_form
        NODISCARD std::optional<vector3> refraction(const vector3& normal, double refractive_ratio) const;

        /// \brief Calculates the refraction of this vector through a normal
        ///        The result will be an outgoing normalized vector
        /// \param normal The normal vector, will be normalized for you
        /// \param refractive_ratio The refractive index ratio of the two mediums, like air and water
        /// \return The refracted vector, if any degenerate case is found, it will return std::nullopt
        /// \note The vector and normal vector must have a length greater than zero
        /// \note The refractive medium2 must be greater than zero.
        /// \note The refractive index ratio must be greater than zero
        /// \note There mustn't be total internal reflection
        /// \see https://en.wikipedia.org/wiki/Refractive_index
        /// \see https://en.wikipedia.org/wiki/Snell%27s_law#Vector_form
        NODISCARD std::optional<vector3> refraction(const vector3& normal, double medium1, double medium2) const;

        /// \brief Print the vector to an output stream
        /// \param os The output stream
        /// \return The output stream
        std::ostream& print(std::ostream& os) const override;

    }; // class vector3
} // namespace bardrix