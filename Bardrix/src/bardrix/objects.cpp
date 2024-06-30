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

    bool material::operator==(const material& material) const noexcept {
        return bardrix::nearly_equal(ambient_, material.ambient_) &&
               bardrix::nearly_equal(diffuse_, material.diffuse_) &&
               bardrix::nearly_equal(specular_, material.specular_) &&
               bardrix::nearly_equal(shininess_, material.shininess_) &&
               color == material.color;
    }

    bool material::operator!=(const material& material) const noexcept {
        return !(*this == material);
    }

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

        return greater_than_or_nearly_equal(tmax, 0) &&
               greater_than_or_nearly_equal(tmax, tmin) &&
               greater_than_or_nearly_equal(ray.get_length(), tmin);
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

    // SPHERE

    sphere::sphere() : sphere(bardrix::point3(0, 0, 0), 1.0) {}

    sphere::sphere(double radius) : sphere(bardrix::point3(0, 0, 0), radius) {}

    sphere::sphere(const bardrix::point3& position, double radius) : sphere(position, bardrix::material(), radius) {}

    sphere::sphere(bardrix::point3 position, const bardrix::material& material, double radius) :
            position_(std::move(position)),
            material_(material),
            radius_(radius < 0 ? 0 : radius) {}

    void sphere::set_material(const bardrix::material& material) { this->material_ = material; }

    const bardrix::material& sphere::get_material() const { return material_; }

    void sphere::set_position(const bardrix::point3& position) { this->position_ = position; }

    const bardrix::point3& sphere::get_position() const { return position_; }


    const double& sphere::get_radius() const { return radius_; }

    void sphere::set_radius(double radius) { radius_ = radius < 0 ? 0 : radius; }

    bardrix::vector3 sphere::normal_at(const bardrix::point3& intersection) const {
        return position_.vector_to(intersection).normalized();
    }

    std::optional<bardrix::point3> sphere::intersection(const bardrix::ray& ray) const {
        // Get direction of the ray
        bardrix::vector3 direction = ray.get_direction();

        // Gets vector from points: ray origin and sphere center
        bardrix::vector3 ray_to_sphere_vector = ray.position.vector_to(position_);

        // Get dot product of origin-center-vector and normalized direction
        const double dot = ray_to_sphere_vector.dot(direction);

        // Turn unit vector direction into a vector direction
        direction *= dot;

        // Length from ray origin to sphere center
        ray_to_sphere_vector = direction - ray_to_sphere_vector;

        // vec.dot(vec) == |vec|^2
        const double distance_squared = ray_to_sphere_vector.dot(ray_to_sphere_vector);

        // Radius^2
        const double radius_squared = radius_ * radius_;

        if (distance_squared > radius_squared)
            return std::nullopt; // A smart way to check if ray intersects before taking the sqrt

        // Calculate distance to intersection
        const double distance = dot - std::sqrt(radius_squared - distance_squared);

        // If we intersect sphere return the length
        return (distance < ray.get_length() && distance > 0)
               ? std::optional(ray.position + ray.get_direction() * distance)
               : std::nullopt;
    }

    bardrix::bounding_box sphere::bounding_box() const {
        return { position_ - radius_, position_ + radius_ };
    }

    bool sphere::operator==(const sphere& sphere) const noexcept {
        return position_ == sphere.position_ && material_ == sphere.material_ &&
               bardrix::nearly_equal(radius_, sphere.radius_);
    }

    bool sphere::operator!=(const sphere& sphere) const noexcept {
        return !(*this == sphere);
    }

} // namespace bardrix