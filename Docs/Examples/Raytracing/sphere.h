//
// Created by Bardio on 22/05/2024.
//

#include <bardrix/objects.h>

/// \brief Sphere shape
class sphere : public bardrix::shape {
protected:
    /// \brief Radius of the sphere
    double radius_;

    // \brief Material of the sphere
    bardrix::material material_;

    /// \brief Center of the sphere
    bardrix::point3 position_;

public:
    // CONSTRUCTORS

    /// \brief Default constructor for sphere (radius = 1, position = {0, 0, 0}, material = (color = white, ambient = 0, diffuse = 1, specular = 0, shininess = 0))
    sphere();

    /// \brief Constructor for sphere (position = {0, 0, 0}, material = (color = white, ambient = 0, diffuse = 1, specular = 0, shininess = 0))
    /// \param radius The radius of the sphere
    explicit sphere(double radius);

    /// \brief Constructor for sphere (material (color = white, ambient = 0, diffuse = 1, specular = 0, shininess = 0))
    /// \param radius The radius of the sphere
    /// \param position The position of the sphere
    sphere(double radius, const bardrix::point3& position);

    /// \brief Constructor for sphere
    /// \param radius The radius of the sphere
    /// \param position The position of the sphere
    /// \param material The material of the sphere
    sphere(double radius, const bardrix::point3& position, const bardrix::material& material);

    // GETTERS/SETTERS
    NODISCARD const bardrix::material& get_material() const override;
    NODISCARD const bardrix::point3& get_position() const override;
    void set_material(const bardrix::material& material) override;
    void set_position(const bardrix::point3& position) override;

    // RAYTRACING

    /// \brief Get the normal at a point on the sphere
    /// \param intersection The point to get the normal at
    /// \return The normal at the point
    /// \example bardrix::vector3 normal = sphere.normal_at(intersection);
    NODISCARD bardrix::vector3 normal_at(const bardrix::point3& intersection) const override;

    /// \brief Get the intersection point of a ray with the sphere
    /// \param ray The ray to check for intersection
    /// \return The intersection point if it exists, otherwise std::nullopt (this means no intersection)
    /// \example std::optional<bardrix::point3> intersection = sphere.intersection(ray);
    /// \example if (intersection.has_value()) { /* Do something with the intersection point */ }
    NODISCARD std::optional<bardrix::point3> intersection(const bardrix::ray& ray) const override;
}; // class sphere