//
// Created by Bardio on 22/05/2024.
//

#include <bardrix/objects.h>

/// \brief Sphere shape
class sphere : public bardrix::shape {
protected:
    /// \brief Radius of the sphere
    double radius_;

    // Material of the sphere (not used currently)
    bardrix::material material_;

    /// \brief Center of the sphere
    bardrix::point3 position_;

public:
    // CONSTRUCTORS

    explicit sphere(double radius);
    sphere(double radius, const bardrix::point3& position);

    // GETTERS/SETTERS
    NODISCARD const bardrix::material& get_material() const override;
    NODISCARD const bardrix::point3& get_position() const override;
    void set_material(const bardrix::material& material) override;
    void set_position(const bardrix::point3& position) override;

    // RAYTRACING

    NODISCARD bardrix::vector3 normal_at(const bardrix::point3& point) const override;
    NODISCARD std::optional<bardrix::point3> intersection(const bardrix::ray& ray) const override;
}; // class sphere