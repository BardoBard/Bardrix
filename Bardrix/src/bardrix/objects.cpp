//
// Created by Bardio on 09/05/2024.
//

#include <bardrix/objects.h>

namespace bardrix {

    /// MATERIAL

    material::material() noexcept: material(0, 1, 0, 0, bardrix::color::white()) {}

    material::material(const double ambient, const double diffuse, const double specular,
                       const double shininess) noexcept
            : material(ambient, diffuse, specular, shininess, color::white()) {}

    material::material(const double ambient, const double diffuse, const double specular, const double shininess,
                       const bardrix::color& color) noexcept: color(color) {
        set_ambient(ambient);
        set_diffuse(diffuse);
        set_specular(specular);
        set_shininess(shininess);
    }

    double material::get_ambient() const { return ambient_; }

    void material::set_ambient(const double ambient) { ambient_ = std::clamp(ambient, 0.0, 1.0); }

    double material::get_diffuse() const { return diffuse_; }

    void material::set_diffuse(const double diffuse) {
        diffuse_ = std::clamp(diffuse, 0.0, 1.0);
    }

    double material::get_specular() const { return specular_; }

    void material::set_specular(const double specular) {
        specular_ = std::clamp(specular, 0.0, 1.0);
    }

    double material::get_shininess() const { return shininess_; }

    void material::set_shininess(const double shininess) { shininess_ = std::max(1.0, shininess); }

    /// BOUDING BOX

    bounding_box::bounding_box(const point3& min, const point3& max) noexcept: min(min), max(max) {}

    bool bounding_box::inside(const bardrix::point3& point) const noexcept {
        bool one = point.x >= min.x && point.x <= max.x;
        bool two = point.y >= min.y && point.y <= max.y;
        bool three = point.z >= min.z && point.z <= max.z;
        return one && two && three;
    }

    bool bounding_box::inside(const bounding_box& box) const noexcept {
        return (min.x <= box.max.x && max.x >= box.min.x &&
                min.y <= box.max.y && max.y >= box.min.y &&
                min.z <= box.max.z && max.z >= box.min.z);
    }

    point3 bounding_box::center() const noexcept {
        return { (min.x + max.x) / 2,
                 (min.y + max.y) / 2,
                 (min.z + max.z) / 2 };
    }

    double bounding_box::width() const noexcept {
        return max.x - min.x;
    }

    double bounding_box::height() const noexcept {
        return max.y - min.y;
    }

    double bounding_box::depth() const noexcept {
        return max.z - min.z;
    }

    double bounding_box::volume() const noexcept {
        return width() * height() * depth();
    }

    double bounding_box::area() const noexcept {
        return 2 * (width() * height() + width() * depth() + height() * depth());
    }

    double bounding_box::diagonal() const noexcept {
        return min.vector_to(max).length();
    }

} // namespace bardrix