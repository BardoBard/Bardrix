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

    void bounding_box::set_min_max(const point3& min, const point3& max) noexcept {
        min_ = point3(std::min(min.x, max.x), std::min(min.y, max.y), std::min(min.z, max.z));
        max_ = point3(std::max(min.x, max.x), std::max(min.y, max.y), std::max(min.z, max.z));
    }

    bool bounding_box::inside(const bardrix::point3& point) const noexcept {
        return greater_than_or_nearly_equal(point.x, min_.x) && less_than_or_nearly_equal(point.x, max_.x) &&
               greater_than_or_nearly_equal(point.y, min_.y) && less_than_or_nearly_equal(point.y, max_.y) &&
               greater_than_or_nearly_equal(point.z, min_.z) && less_than_or_nearly_equal(point.z, max_.z);
    }

    bool bounding_box::inside(const bounding_box& box) const noexcept {
        return inside(box.min_) && inside(box.max_);
    }

    bool bounding_box::intersects(const bounding_box& box) const noexcept {
        return less_than_or_nearly_equal(min_.x, box.max_.x) && greater_than_or_nearly_equal(max_.x, box.min_.x) &&
               less_than_or_nearly_equal(min_.y, box.max_.y) && greater_than_or_nearly_equal(max_.y, box.min_.y) &&
               less_than_or_nearly_equal(min_.z, box.max_.z) && greater_than_or_nearly_equal(max_.z, box.min_.z);
    }

    bool bounding_box::intersects(const bardrix::ray& ray) const noexcept {
        vector3 ray_dir = bardrix::vector3(1 / ray.get_direction().x, 1 / ray.get_direction().y,
                                           1 / ray.get_direction().z);

        const double t1 = (min_.x - ray.position.x) * ray_dir.x;
        const double t2 = (max_.x - ray.position.x) * ray_dir.x;
        const double t3 = (min_.y - ray.position.y) * ray_dir.y;
        const double t4 = (max_.y - ray.position.y) * ray_dir.y;
        const double t5 = (min_.z - ray.position.z) * ray_dir.z;
        const double t6 = (max_.z - ray.position.z) * ray_dir.z;

        const double tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
        const double tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

        return greater_than_or_nearly_equal(tmax, tmin) && greater_than_or_nearly_equal(ray.get_length(), tmin);
    }

    bounding_box bounding_box::merged(const bounding_box& box) const noexcept {
        bounding_box temp = *this;
        temp.merge(box);
        return temp;
    }

    const bounding_box& bounding_box::merge(const bounding_box& box) noexcept {
        min_ = point3(std::min(min_.x, box.min_.x), std::min(min_.y, box.min_.y), std::min(min_.z, box.min_.z));
        max_ = point3(std::max(max_.x, box.max_.x), std::max(max_.y, box.max_.y), std::max(max_.z, box.max_.z));
        return *this;
    }

    bounding_box bounding_box::expanded(double distance) const noexcept {
        bounding_box temp = *this;
        temp.expand(distance);
        return temp;
    }

    const bounding_box& bounding_box::expand(double distance) noexcept {
        min_ -= distance;
        max_ += distance;

        // We cannot shrink past the center
        if (width() < 0) min_.x = max_.x = center().x;
        if (height() < 0) min_.y = max_.y = center().y;
        if (depth() < 0) min_.z = max_.z = center().z;

        return *this;
    }

    bool bounding_box::is_empty() const noexcept {
        return min_ == max_;
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

    bounding_box bounding_box::operator+(const vector3& vector) const noexcept {
        bounding_box temp = *this;
        temp.min_ += vector;
        temp.max_ += vector;
        return temp;
    }

    bounding_box bounding_box::operator+(double value) const noexcept {
        bounding_box temp = *this;
        temp.min_ += value;
        temp.max_ += value;
        return temp;
    }

    const bounding_box& bounding_box::operator+=(const vector3& vector) noexcept {
        min_ += vector;
        max_ += vector;
        return *this;
    }

    const bounding_box& bounding_box::operator+=(double value) noexcept {
        min_ += value;
        max_ += value;
        return *this;
    }

    bounding_box bounding_box::operator-(const vector3& vector) const noexcept {
        bounding_box temp = *this;
        temp.min_ -= vector;
        temp.max_ -= vector;
        return temp;
    }

    bounding_box bounding_box::operator-(double value) const noexcept {
        bounding_box temp = *this;
        temp.min_ -= value;
        temp.max_ -= value;
        return temp;
    }

    const bounding_box& bounding_box::operator-=(const vector3& vector) noexcept {
        min_ -= vector;
        max_ -= vector;
        return *this;
    }

    const bounding_box& bounding_box::operator-=(double value) noexcept {
        min_ -= value;
        max_ -= value;
        return *this;
    }

    bool bounding_box::operator==(const bounding_box& box) const noexcept {
        return min_ == box.min_ && max_ == box.max_;
    }

    bool bounding_box::operator!=(const bounding_box& box) const noexcept {
        return min_ != box.min_ || max_ != box.max_;
    }

    std::ostream& operator<<(std::ostream& os, const bounding_box& box) {
        os << "Bounding Box:";
        os << " (Min: " << box.get_min();
        os << ", Max: " << box.get_max() << ")";
        return os;
    }

} // namespace bardrix