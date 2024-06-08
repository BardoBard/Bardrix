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

    bounding_box::bounding_box(const point3& min, const point3& max) noexcept {
        this->min_ = point3(std::min(min.x, max.x), std::min(min.y, max.y), std::min(min.z, max.z));
        this->max_ = point3(std::max(min.x, max.x), std::max(min.y, max.y), std::max(min.z, max.z));
    }

    const bardrix::point3& bounding_box::get_min() const noexcept { return min_; }

    const bardrix::point3& bounding_box::get_max() const noexcept { return max_; }

    void bounding_box::set_min(const bardrix::point3& min) noexcept {
        min_ = point3(std::min(min.x, max_.x), std::min(min.y, max_.y), std::min(min.z, max_.z));
    }

    void bounding_box::set_max(const bardrix::point3& max) noexcept {
        max_ = point3(std::max(min_.x, max.x), std::max(min_.y, max.y), std::max(min_.z, max.z));
    }

    bool bounding_box::inside(const bardrix::point3& point) const noexcept {
        return greater_than_or_nearly_equal(point.x, min_.x) && less_than_or_nearly_equal(point.x, max_.x) &&
               greater_than_or_nearly_equal(point.y, min_.y) && less_than_or_nearly_equal(point.y, max_.y) &&
               greater_than_or_nearly_equal(point.z, min_.z) && less_than_or_nearly_equal(point.z, max_.z);
    }

    bool bounding_box::inside(const bounding_box& box) const noexcept {
        return inside(box.min_) && inside(box.max_);
    }


    bounding_box bounding_box::merge(const bounding_box& box) const noexcept {
        return {{ std::min(min_.x, box.min_.x), std::min(min_.y, box.min_.y), std::min(min_.z, box.min_.z) },
                { std::max(max_.x, box.max_.x), std::max(max_.y, box.max_.y), std::max(max_.z, box.max_.z) }};
    }

    point3 bounding_box::center() const noexcept {
        return { (min_.x + max_.x) / 2,
                 (min_.y + max_.y) / 2,
                 (min_.z + max_.z) / 2 };
    }

    double bounding_box::width() const noexcept {
        return max_.x - min_.x;
    }

    double bounding_box::height() const noexcept {
        return max_.y - min_.y;
    }

    double bounding_box::depth() const noexcept {
        return max_.z - min_.z;
    }

    double bounding_box::volume() const noexcept {
        return width() * height() * depth();
    }

    double bounding_box::area() const noexcept {
        return 2 * (width() * height() + width() * depth() + height() * depth());
    }

    double bounding_box::diagonal() const noexcept {
        return min_.vector_to(max_).length();
    }

    bool bounding_box::is_hit(const bardrix::ray& ray) const noexcept {
        // my attempt of branch-less intersection

        double tmin, tmax, tymin, tymax, tzmin, tzmax;
        vector3 ray_dir = ray.get_direction();

        // x axis
        {
            bool positive_x = greater_than_or_nearly_equal(ray_dir.x, 0);
            tmin = (positive_x ? (min_.x - ray.position.x) / ray_dir.x : (max_.x - ray.position.x) / ray_dir.x);
            tmax = (positive_x ? (max_.x - ray.position.x) / ray_dir.x : (min_.x - ray.position.x) / ray_dir.x);
        }

        // y axis
        {
            bool positive_y = greater_than_or_nearly_equal(ray_dir.y, 0);
            tymin = (positive_y ? (min_.y - ray.position.y) / ray_dir.y : (max_.y - ray.position.y) / ray_dir.y);
            tymax = (positive_y ? (max_.y - ray.position.y) / ray_dir.y : (min_.y - ray.position.y) / ray_dir.y);
        }

        if ((tmin > tymax) || (tymin > tmax)) return false;

        tmin = std::max(tmin, tymin);
        tmax = std::min(tmax, tymax);

        // z axis
        {
            bool positive_z = greater_than_or_nearly_equal(ray_dir.z, 0);
            tzmin = (positive_z ? (min_.z - ray.position.z) / ray_dir.z : (max_.z - ray.position.z) / ray_dir.z);
            tzmax = (positive_z ? (max_.z - ray.position.z) / ray_dir.z : (min_.z - ray.position.z) / ray_dir.z);
        }

        if ((tmin > tzmax) || (tzmin > tmax)) return false;

        return tmin < ray.get_length();
    }

} // namespace bardrix