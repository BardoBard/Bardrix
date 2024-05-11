//
// Created by Bardio on 09/05/2024.
//

#include <bardrix/objects.h>

namespace bardrix {

    material::material(const double ambient, const double diffuse, const double shininess) : material(color::white(), ambient, diffuse, shininess) {}

    material::material(const bardrix::color& color, const double ambient, const double diffuse, const double shininess) : color(color) {
        set_ambient(ambient);
        set_diffuse(diffuse);
        set_shininess(shininess);
    }

    double material::get_ambient() const { return ambient_; }

    void material::set_ambient(const double ambient) { ambient_ = std::clamp(ambient, 0.0, 1.0); }

    double material::get_diffuse() const { return diffuse_; }

    void material::set_diffuse(const double diffuse) {
        diffuse_ = std::clamp(diffuse, 0.0, 1.0);
        specular_ = 1 - diffuse_;
    }

    double material::get_specular() const { return specular_; }

    void material::set_specular(const double specular) {
        specular_ = std::clamp(specular, 0.0, 1.0);
        diffuse_ = 1 - specular_;
    }

    double material::get_shininess() const { return shininess_; }

    void material::set_shininess(const double shininess) { shininess_ = std::clamp(shininess, 0.0, 1.0); }

} // namespace bardrix