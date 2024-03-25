//
// Created by Bard on 14/03/2024.
//

#pragma once

#include <bardrix/bardrix.h>
#include <bardrix/dimension3.h>
#include <bardrix/vector3.h>

namespace bardrix {

    /// \brief A 3D point class
    /// \brief This class inherits from dimension3
    class point3 : public dimension3 {

    public:
        /// \brief Default constructor for point3, (0,0,0)
        point3() = default;

        /// \brief Constructor for point3, initializes x, y and z
        /// \param x Initial x value
        /// \param y Initial y value
        /// \param z Initial z value
        point3(double x, double y, double z);

        /// \brief Distance between two points
        /// \param point3 The other point
        /// \return The distance between the two points
        NODISCARD double distance(const point3& point3) const noexcept;

        /// \brief Distance between two points squared
        /// \param point3 The other point
        /// \details This method is faster than distance, as it does not calculate the square root
        /// \return The distance between the two points squared
        NODISCARD double distance_squared(const point3& point3) const noexcept;

        /// \brief Midpoint between two points
        /// \param point3 The other point
        /// \return The midpoint between the two points
        NODISCARD point3 midpoint(const point3& point3) const noexcept;

        /// \brief Create a vector from this point to another point
        /// \param point3 The other point
        /// \return The vector from this point to the other point
        NODISCARD vector3 vector_to(const point3& point3) const noexcept;

        /// \brief Add a vector to a point
        /// \param vector3 The vector to add
        /// \return The point with the vector added
        NODISCARD point3 operator+(const vector3& vector3) const noexcept;

        /// \brief Subtract a vector from a point
        /// \param vector3 The vector to subtract
        /// \return The point with the vector subtracted
        NODISCARD point3 operator-(const vector3& vector3) const noexcept;

        /// \brief Print the point to an output stream
        /// \param os The output stream
        /// \return The output stream
        std::ostream& print(std::ostream& os) const override;

    }; // class point3

} // namespace bardrix