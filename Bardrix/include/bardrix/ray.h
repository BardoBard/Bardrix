//
// Created by Bardio on 17/03/2024.
//

#pragma once

#include <bardrix/bardrix.h>
#include <bardrix/vector3.h>
#include <bardrix/point3.h>

namespace bardrix {

    /// \brief A 3D ray class
    /// \details A ray is defined by a position and a direction, it also has a length
    class ray {

    public:
        /// \brief The position of the ray, the origin
        point3 position;

    private:
        /// \brief The direction of the ray, it's normalized
        vector3 direction_;

        /// \brief The length of the ray, it cannot be less than 0
        double length_;

    public:
        /// \brief Default constructor for ray, position (0,0,0)
        /// \param direction The direction of the ray, it'll be normalized
        explicit ray(const vector3& direction) noexcept;

        /// \brief Constructor for ray, initializes position and direction
        /// \param position The position of the ray
        /// \param direction The direction of the ray, it'll be normalized
        ray(const point3& position, const vector3& direction) noexcept;

        /// \brief Constructor for ray, initializes position, direction and length
        /// \param position The position of the ray
        /// \param direction The direction of the ray, it'll be normalized
        /// \param length The length of the ray
        ray(point3  position, const vector3& direction, double length) noexcept;

        /// \brief Get the direction of the ray
        /// \return The direction of the ray
        NODISCARD const vector3& get_direction() const noexcept;

        /// \brief Set the direction of the ray, direction cannot have length of 0
        /// \param direction The new direction of the ray
        void set_direction(const vector3& direction) noexcept;

        /// \brief Get the length of the ray
        /// \return The length of the ray
        NODISCARD double get_length() const noexcept;

        /// \brief Sets the length of the ray
        /// \param length The new length of the ray
        /// \details If the length is less than 0, it will be set to 0
        void set_length(double length) noexcept;

        /// \brief Gets the point at the end of the ray
        /// \return The point at the end of the ray
        NODISCARD point3 get_end() const noexcept;

        /// \brief Get the point at a distance from the position
        /// \param distance The distance from the position
        /// \return The point at the distance from the position
        /// \details If the distance is less than 0, it will return the position
        NODISCARD point3 point_at(double distance) const noexcept;

        /// \brief Print the ray to an output stream
        /// \param os The output stream
        /// \return The output stream
        std::ostream& print(std::ostream& os) const;

        /// \brief Operator to print the ray to an output stream
        /// \param os The output stream
        /// \param r The ray to print
        /// \return The output stream
        friend std::ostream& operator<<(std::ostream& os, const ray& r);

        /// \brief Equality operator
        /// \param r The ray to compare
        /// \return True if the rays are equal
        /// \example ray(point3(1, 2, 3), vector3(1, 0, 0)) == ray(point3(1, 2, 3), vector3(1, 0, 0)) -> true
        bool operator==(const ray& r) const noexcept;

        /// \brief Inequality operator
        /// \param r The ray to compare
        /// \return True if the rays are not equal
        /// \example ray(point3(1, 2, 3), vector3(1, 0, 0)) != ray(point3(1, 2, 3), vector3(0, 1, 0)) -> true
        bool operator!=(const ray& r) const noexcept;

    }; // class ray

} // namespace bardrix