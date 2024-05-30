//
// Created by Bardio on 09/05/2024.
//

#include <bardrix/objects.h>

namespace bardrix {

    material::material() noexcept : material(0, 1, 0, 0, bardrix::color::white()) {}

    material::material(const double ambient, const double diffuse, const double specular, const double shininess) noexcept
            : material(ambient, diffuse, specular, shininess, color::white()) {}

    material::material(const double ambient, const double diffuse, const double specular, const double shininess,
                       const bardrix::color& color) noexcept : color(color) {
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

} // namespace bardrix