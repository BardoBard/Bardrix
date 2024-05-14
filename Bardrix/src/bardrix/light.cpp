//
// Created by Bardio on 30/03/2024.
//

#include <bardrix/light.h>

namespace bardrix {

    light::light(point3 position, double intensity, const bardrix::color& color) noexcept
            : position{ std::move(position) }, color{ color } {
        set_intensity(intensity);
    }

    void light::set_intensity(double intensity) noexcept {
        this->intensity_ = less_than_or_nearly_equal(intensity, 0) ? 0 : intensity;
    }

    double light::get_intensity() const noexcept { return intensity_; }

    double light::inverse_square_law_squared(const double distance_squared) const noexcept {
        if (nearly_equal(distance_squared, 0)) return HUGE_VAL;
        return intensity_ / distance_squared;
    }

    double light::inverse_square_law(const point3& point) const noexcept {
        return inverse_square_law_squared(position.distance_squared(point));
    }

    double light::inverse_square_law(const double distance) const noexcept {
        return inverse_square_law_squared(distance * distance);
    }

    bool light::operator==(const light& other) const noexcept {
        return position == other.position && color == other.color && nearly_equal(intensity_, other.intensity_);
    }

    bool light::operator!=(const light& other) const noexcept {
        return !(*this == other);
    }

    std::ostream& light::print(std::ostream& os) const {
        os << "Light: " << position << ", Intensity: " << intensity_ << ", Color: " << color;
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const light& light) {
        return light.print(os);
    }

} // bardrix