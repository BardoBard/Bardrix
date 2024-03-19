//
// Created by Bard on 19/03/2024.
//

#include <bardrix/camera.h>

namespace bardrix {
    camera::camera() noexcept: camera(point3(), vector3(0, 0, 1), 800, 600, 90) {}


    camera::camera(const point3& position, const vector3& direction,
                   unsigned int screen_size) noexcept: camera(position, direction, screen_size, screen_size,
                                                              90) {}

    camera::camera(point3 position, const vector3& direction,
                   unsigned int screen_width, unsigned int screen_height, unsigned int fov) noexcept:
            position_(std::move(position)), width_(screen_width), height_(screen_height) {
        set_fov(fov);
        set_direction(direction);
    }

    void camera::update_screen_vectors() noexcept {
        vector3 arbitrary_vector = {1, 0, 0}; //random vector
        if (direction_ == arbitrary_vector)
            //other random vector, if direction is the same as the first random vector
            arbitrary_vector = {0, 1, 0};

        const vector3 cross_factor = direction_.cross(arbitrary_vector).normalized();

        //get horizontal and vertical vector
        right_ = direction_.cross(cross_factor).normalized() * fov_half_tan_;
        up_ = right_.cross(direction_).normalized() * fov_half_tan_;
    }

    const vector3& camera::get_direction() const noexcept {
        return direction_;
    }

    void camera::set_direction(const vector3& direction) noexcept {
        direction_ = direction == vector3() ? vector3(0, 0, 1) : direction.normalized();
        update_screen_vectors();
    }

    unsigned int camera::get_fov() const noexcept {
        return fov_degrees_;
    }

    void camera::set_fov(unsigned int fov) noexcept {
        fov = (fov >= 180) ? 179 : fov;
        fov_degrees_ = fov;
        fov_half_tan_ = std::tan(degrees_to_radians(fov) / 2);

        update_screen_vectors();
    }

    ray camera::shoot_ray(unsigned int x, unsigned int y, const double distance) const noexcept {
        if (x >= width_ || y >= height_)
            return {};

        const double ratio_width = x / static_cast<double>(width_);
        const double ratio_height = y / static_cast<double>(height_);

        const vector3 horizontal = right_ * 2 * ratio_width;
        const vector3 vertical = up_ * 2 * ratio_height;

        const point3 top_left = position_ + direction_ - right_ - up_;

        return {position_, position_.vector_to(top_left + horizontal - vertical), distance};
    }

    void camera::look_at(const point3& point) noexcept {
        set_direction(position_.vector_to(point));
    }

} // namespace bardrix