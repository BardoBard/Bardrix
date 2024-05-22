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
        point3 position;

    private:
        // Screen properties

        /// \brief The width and height of the screen
        int width_ = 800, height_ = 600;

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

    protected:
        /// \brief Updates the up and right vectors
        void update_screen_vectors() noexcept;

    public:
        /// \brief Default constructor for camera
        /// \details The position will be (0,0,0)
        /// \details The direction will be (0,0,1)
        /// \details The fov will be 90 degrees
        /// \details The screen size will be 800x600
        camera() noexcept;

        /// \brief Constructor for camera, initializes position and direction
        /// \param position The position of the camera
        /// \param direction The direction of the camera, it'll be normalized
        /// \details The fov will be 90 degrees by default
        /// \details The screen size will be 800x600 by default
        /// \details If the direction is (0,0,0), it will be set to (0,0,1)
        camera(const bardrix::point3& position, const bardrix::vector3& direction) noexcept;

        /// \brief Constructor for camera, initializes position, direction and screen size (width and height)
        /// \param position The position of the camera
        /// \param direction The direction of the camera, it'll be normalized
        /// \param screen_size The size of the screen, it'll be the width and height
        /// \details The fov will be 90 degrees by default
        /// \details If the direction is (0,0,0), it will be set to (0,0,1)
        camera(const bardrix::point3& position, const bardrix::vector3& direction, int screen_size) noexcept;

        /// \brief Constructor for camera, initializes position, direction, screen size (width and height) and fov
        /// \param position The position of the camera
        /// \param direction The direction of the camera, it'll be normalized
        /// \param screen_width The width of the screen, default 800
        /// \param screen_height The height of the screen, default 600
        /// \param fov The field of view of the camera, in degrees, default 90
        /// \details If the fov is greater than or equal to 180, it will be set to 179
        /// \details If the direction is (0,0,0), it will be set to (0,0,1)
        camera(bardrix::point3 position, const bardrix::vector3& direction, int screen_width, int screen_height, unsigned int fov) noexcept;

        /// \brief Get the direction of the camera
        /// \return The direction of the camera
        NODISCARD const bardrix::vector3& get_direction() const noexcept;

        /// \brief Set the direction of the camera, direction cannot have length of 0
        /// \param direction The new direction of the camera
        /// \details If the length of the direction is 0, it will make the direction (0,0,1)
        void set_direction(const bardrix::vector3& direction) noexcept;

        /// \brief Get the field of view of the camera
        /// \return The field of view of the camera
        /// \details The fov is in degrees
        NODISCARD unsigned int get_fov() const noexcept;

        /// \brief Set the field of view of the camera
        /// \param fov The new field of view of the camera
        /// \details The fov is in degrees
        /// \details If the fov is greater than or equal to 180, it will be set to 179
        void set_fov(unsigned int fov) noexcept;

        /// \brief Get the width of the screen
        /// \return The width of the screen
        NODISCARD int get_width() const noexcept;

        /// \brief Sets the width of the screen
        /// \param width The new width of the screen
        /// \details If the width is less than 0, it will be set to 0
        void set_width(int width) noexcept;

        /// \brief Get the height of the screen
        /// \return The height of the screen
        NODISCARD int get_height() const noexcept;

        /// \brief Sets the height of the screen
        /// \param height The new height of the screen
        /// \details If the height is less than 0, it will be set to 0
        void set_height(int height) noexcept;

        /// \brief Shoots a ray from the camera to the screen
        /// \param x The x position of the screen
        /// \param y The y position of the screen
        /// \return The ray from the camera to the screen, only if the x and y are less than the width and height
        /// \details If the x or y is greater than or equal to the width or height, it will return an empty optional
        /// \details If the x or y is less than 0, it will return an empty optional
        NODISCARD std::optional<bardrix::ray> shoot_ray(int x, int y, double distance) const noexcept;

        /// \brief Looks at a point from the camera
        /// \param point The point to look at
        /// \details If the point is the same as the position, it will not change the direction
        void look_at(const bardrix::point3& point) noexcept;

        /// \brief Prints the camera to the output stream
        /// \param os The output stream
        /// \param camera The camera to print
        /// \return The output stream
        /// \details The output will be in the format: "Position: (x, y, z), Direction: (x, y, z), width, height, fov"
        friend std::ostream& operator<<(std::ostream& os, const bardrix::camera& camera) noexcept;

    }; // class camera
} // namespace bardrix