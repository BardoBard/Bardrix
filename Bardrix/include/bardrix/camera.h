//
// Created by Bard on 19/03/2024.
//

#pragma once

#include <bardrix/bardrix.h>
#include <bardrix/vector3.h>
#include <bardrix/point3.h>
#include <bardrix/ray.h>
#include <bardrix/math.h>

namespace bardrix {

    class camera {

    public:
        /// \brief The position of the camera
        point3 position_;

        /// \brief The width and height of the screen
        unsigned int width_ = 800, height_ = 600;

    private:
        // Screen properties

        /// \brief The horizontal and vertical directions of the screen
        vector3 up_, right_;

        // Camera properties

        /// \brief The direction of the camera, it's normalized
        vector3 direction_ = vector3(0, 0, 1);

        /// \brief The field of view of the camera
        /// \note The fov is in radians, taken from the tangent of the fov in degrees divided by 2
        /// \details Tan(fov/2), where fov is in radians
        double fov_half_tan_ = 1; // 90 degrees

        /// \brief The field of view of the camera in degrees
        /// \details The fov is in degrees
        unsigned int fov_degrees_ = 90; // 90 degrees

    private:
        /// \brief Updates the up and right vectors
        void update_screen_vectors() noexcept;

    public:
        /// \brief Default constructor for camera, (0,0,0) direction (0,0,1), fov 90, width 800, height 600
        camera() noexcept;

        /// \brief Constructor for camera, initializes position, direction and screen size (width and height)
        /// \param position The position of the camera
        /// \param direction The direction of the camera, it'll be normalized
        /// \param screen_size The size of the screen, it'll be the width and height
        /// \details The fov will be 90 degrees by default
        /// \details If the fov is greater than or equal to 180, it will be set to 179
        camera(const point3& position, const vector3& direction, unsigned int screen_size) noexcept;

        /// \brief Constructor for camera, initializes position, direction, screen size (width and height) and fov
        /// \param position The position of the camera
        /// \param direction The direction of the camera, it'll be normalized
        /// \param screen_width The width of the screen, default 800
        /// \param screen_height The height of the screen, default 600
        /// \param fov The field of view of the camera, in degrees, default 90
        /// \details If the fov is greater than or equal to 180, it will be set to 179
        camera(point3 position, const vector3& direction, unsigned int screen_width = 800,
               unsigned int screen_height = 600, unsigned int fov = 90) noexcept;

        /// \brief Get the direction of the camera
        /// \return The direction of the camera
        NODISCARD const vector3& get_direction() const noexcept;

        /// \brief Set the direction of the camera, direction cannot have length of 0
        /// \param direction The new direction of the camera
        /// \details If the length of the direction is 0, it will make the direction (0,0,1)
        void set_direction(const vector3& direction) noexcept;

        /// \brief Get the field of view of the camera
        /// \return The field of view of the camera
        /// \details The fov is in degrees
        NODISCARD unsigned int get_fov() const noexcept;

        /// \brief Set the field of view of the camera
        /// \param fov The new field of view of the camera
        /// \details The fov is in degrees
        /// \details If the fov is greater than or equal to 180, it will be set to 179
        void set_fov(unsigned int fov) noexcept;

        /// \brief Shoots a ray from the camera to the screen
        /// \param x The x position of the screen
        /// \param y The y position of the screen
        /// \return The ray from the camera to the screen
        NODISCARD ray shoot_ray(unsigned int x, unsigned int y, double distance) const noexcept;

        /// \brief Looks at a point from the camera
        /// \param point The point to look at
        void look_at(const point3& point) noexcept;

    }; // class camera
} // namespace bardrix