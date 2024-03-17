//
// Created by Bardio on 17/03/2024.
//

#pragma once

#include <bardrix/bardrix.h>
#include <bardrix/vector3.h>
#include <bardrix/point3.h>

namespace bardrix {

    /// \brief A 3D ray class
    class ray {

    private:
        point3 origin_;
        vector3 direction_;
        double length_;

    public:
        /// \brief Default constructor for ray, (0,0,0) direction (0,0,1), length 1
        ray();

        /// \brief Constructor for ray, initializes origin and direction
        /// \param origin The origin of the ray
        /// \param direction The direction of the ray, it'll be normalized
        ray(const point3& origin, const vector3& direction);

        /// \brief Constructor for ray, initializes origin, direction and length
        /// \param origin The origin of the ray
        /// \param direction The direction of the ray, it'll be normalized
        /// \param length The length of the ray
        ray(point3 origin, const vector3& direction, double length);

        /// \brief Get the origin of the ray
        /// \return The origin of the ray
        NODISCARD const point3& get_origin() const noexcept;

        /// \brief Get the direction of the ray
        /// \return The direction of the ray
        NODISCARD const vector3& get_direction() const noexcept;

        /// \brief Get the length of the ray
        /// \return The length of the ray
        NODISCARD double get_length() const noexcept;

        /// \brief Get the point at a distance from the origin
        /// \param distance The distance from the origin
        /// \return The point at the distance from the origin
        NODISCARD point3 point_at(double distance) const noexcept;

        /// \brief Gets the point at the end of the ray
        /// \return The point at the end of the ray
        NODISCARD point3 end() const noexcept;

        /// \brief Print the ray to an output stream
        /// \param os The output stream
        /// \return The output stream
        std::ostream& print(std::ostream& os) const;

    }; // class ray

} // namespace bardrix