//
// Created by Bard on 19/03/2024.
//

#include <bardrix/camera.h>
#include <optional>

namespace bardrix {


    camera::camera() noexcept : camera({ 0, 0, 0 }, { 0, 0, 1 }) {}

    camera::camera(const point3& position, const vector3& direction) noexcept: camera(position, direction, 800, 600,
                                                                                      90) {}

    camera::camera(const point3& position, const vector3& direction,
                   int screen_size) noexcept: camera(position, direction, screen_size, screen_size, 90) {}

    camera::camera(point3 position, const vector3& direction, int screen_width, int screen_height,
                   unsigned int fov) noexcept: position(std::move(position)) {
        set_fov(fov);
        set_direction(direction);
        set_width(screen_width);
        set_height(screen_height);
    }

    void camera::update_screen_vectors() noexcept {
        vector3 arbitrary_vector = { 1, 0, 0 }; //random vector
        if (direction_ == arbitrary_vector)
            //other random vector, if direction is the same as the first random vector
            arbitrary_vector = { 0, 1, 0 };

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

    void camera::set_height(int height) noexcept { this->height_ = height < 0 ? 0 : height; }

    int camera::get_height() const noexcept { return height_; }

    void camera::set_width(int width) noexcept { this->width_ = width < 0 ? 0 : width; }

    int camera::get_width() const noexcept { return width_; }

    std::optional<ray> camera::shoot_ray(int x, int y, const double distance) const noexcept {
        if (x >= width_ || y >= height_ || x < 0 || y < 0)
            return std::nullopt;

        const double ratio_width = x / static_cast<double>(width_);
        const double ratio_height = y / static_cast<double>(height_);

        // horizontal and vertical vectors
        const vector3 horizontal = right_ * 2 * ratio_width;
        const vector3 vertical = up_ * 2 * ratio_height;

        // top left corner of the screen
        const point3 top_left = position + direction_ - right_ + up_;

        return std::make_optional(ray{position, position.vector_to(top_left + horizontal - vertical), distance});
    }

    void camera::look_at(const point3& point) noexcept {
        if (point == position)
            return;

        set_direction(position.vector_to(point));
    }

    std::ostream& operator<<(std::ostream& os, const camera& camera) noexcept {
        return os << "Position: " << camera.position << ", Direction: " << camera.direction_ << ", " << camera.width_
                  << ", " << camera.height_ << ", " << camera.fov_degrees_;
    }

} // namespace bardrix