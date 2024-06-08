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

    /// BOUNDING BOX

    bounding_box::bounding_box(const point3& min, const point3& max) noexcept: min(min), max(max) {}

    bool bounding_box::inside(const bardrix::point3& point) const noexcept {
        return greater_than_or_nearly_equal(point.x, min.x) && less_than_or_nearly_equal(point.x, max.x) &&
               greater_than_or_nearly_equal(point.y, min.y) && less_than_or_nearly_equal(point.y, max.y) &&
               greater_than_or_nearly_equal(point.z, min.z) && less_than_or_nearly_equal(point.z, max.z);
    }

    bool bounding_box::inside(const bounding_box& box) const noexcept {
        return inside(box.min) && inside(box.max);
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

    bool bounding_box::is_hit(const bardrix::ray& ray) const noexcept {
        // my attempt of branch-less intersection

        double tmin, tmax, tymin, tymax, tzmin, tzmax;
        vector3 ray_dir = ray.get_direction();

        // x axis
        {
            bool positive_x = greater_than_or_nearly_equal(ray_dir.x, 0);
            tmin = (positive_x ? (min.x - ray.position.x) / ray_dir.x : (max.x - ray.position.x) / ray_dir.x);
            tmax = (positive_x ? (max.x - ray.position.x) / ray_dir.x : (min.x - ray.position.x) / ray_dir.x);
        }

        // y axis
        {
            bool positive_y = greater_than_or_nearly_equal(ray_dir.y, 0);
            tymin = (positive_y ? (min.y - ray.position.y) / ray_dir.y : (max.y - ray.position.y) / ray_dir.y);
            tymax = (positive_y ? (max.y - ray.position.y) / ray_dir.y : (min.y - ray.position.y) / ray_dir.y);
        }

        if ((tmin > tymax) || (tymin > tmax)) return false;

        tmin = std::max(tmin, tymin);
        tmax = std::min(tmax, tymax);

        // z axis
        {
            bool positive_z = greater_than_or_nearly_equal(ray_dir.z, 0);
            tzmin = (positive_z ? (min.z - ray.position.z) / ray_dir.z : (max.z - ray.position.z) / ray_dir.z);
            tzmax = (positive_z ? (max.z - ray.position.z) / ray_dir.z : (min.z - ray.position.z) / ray_dir.z);
        }

        if ((tmin > tzmax) || (tzmin > tmax)) return false;

        return tmin < ray.get_length();
    }

} // namespace bardrix