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
        /// \brief Default constructor for vector3, (0,0,0)
        vector3() = default;

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

        /// \brief Normalize the vector, making it a unit vector
        /// \throws std::invalid_argument If the length of the vector is 0
        /// \return The normalized vector
        NODISCARD vector3 normalize() const;

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
        /// \throws std::invalid_argument If the length of the vector is 0
        /// \throws std::invalid_argument If the length of the other vector is 0
        /// \note When the angle is 1, the vectors are parallel, when the angle is -1, the vectors are opposite
        /// \details It will normalize this vector and the other vector before calculating the angle
        /// \return The angle between the two vectors [-1, 1]
        NODISCARD double angle(const vector3& vec3) const;

        /// \brief Print the vector to an output stream
        /// \param os The output stream
        /// \return The output stream
        std::ostream& print(std::ostream& os) const override;

    }; // class vector3
} // namespace bardrix