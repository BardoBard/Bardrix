//
// Created by Bardio on 09/05/2024.
//

#pragma once

#include <bardrix/bardrix.h>
#include <bardrix/point3.h>
#include <bardrix/ray.h>
#include <bardrix/color.h>

namespace bardrix {

    /// \brief A material
    /// \details This class represents a material, which is used to define the appearance of an object
    /// \note This is but a base class, it can be inherited to create more complex materials
    class material {

    public:
        /// \brief The color of the material
        class bardrix::color color = bardrix::color::white();

    private:
        /// \brief The ambient coefficient, between 0 and 1
        ///        Ambient light is the light that is already present in the scene, think of it as the minimum light level
        /// \details Ambient light has to be between 0 and 1, where 0 is no ambient light and 1 is full ambient light
        double ambient_ = 0;

        /// \brief The diffuse coefficient, between 0 and 1
        ///        Diffuse light is the light that is reflected off the surface of the object
        ///        Think of it as light that is scattered in all directions when it hits the object
        /// \details Diffuse light has to be between 0 and 1, where 0 is no diffuse light and 1 is full diffuse light
        double diffuse_ = 1;

        /// \brief The specular coefficient, between 0 and 1
        ///        Specular light is the light that is reflected off the surface of the object in a mirror-like way
        ///        Think of it as the light that is reflected in a specific direction when it hits the object
        /// \details Specular light has to be between 0 and 1, where 0 is no specular light and 1 is full specular light
        double specular_ = 0;

        /// \brief The shininess coefficient, between 1 and infinity
        ///        Shininess is the size of the specular highlight
        ///        Think of it as the size of the reflection of the light
        /// \details Shininess has to be between 1 and infinity, where 1 leads to broad highlights and infinity leads to sharp highlights
        double shininess_ = 0;

    public:
        /// \brief Default constructor for material
        /// \note The default material is white with no ambient, full diffuse, no specular and no shininess
        material() noexcept;

        /// \brief Constructor for material
        /// \param ambient The ambient coefficient [0, 1]
        /// \param diffuse The diffuse coefficient [0, 1]
        /// \param specular The specular coefficient [0, 1]
        /// \param shininess The shininess coefficient [1, infinity]
        /// \example material material(0.5, 0.1, 0.9, 50); -> color = white, ambient = 0.5, diffuse = 0.1, specular = 0.9, shininess = 50
        material(double ambient, double diffuse, double specular, double shininess) noexcept;

        /// \brief Constructor for material
        /// \param ambient The ambient coefficient [0, 1]
        /// \param diffuse The diffuse coefficient [0, 1]
        /// \param specular The specular coefficient [0, 1]
        /// \param shininess The shininess coefficient [1, infinity]
        /// \param color The color of the material
        /// \example material material(0.5, 0.1, 0.9, 50, bardrix::color::red()); -> color = red, ambient = 0.5, diffuse = 0.1, specular = 0.9, shininess = 50
        material(double ambient, double diffuse, double specular, double shininess,
                 const bardrix::color& color) noexcept;

        /// \brief Gets the ambient coefficient
        /// \return The ambient coefficient, between 0 and 1
        NODISCARD double get_ambient() const;

        /// \brief Sets the ambient coefficient
        /// \param ambient The ambient coefficient
        /// \note If the ambient coefficient is less than 0, it will be set to 0
        /// \note If the ambient coefficient is greater than 1, it will be set to 1
        /// \example material.set_ambient(0.5); -> ambient = 0.5
        /// \example material.set_ambient(1.8); -> ambient = 1
        void set_ambient(double ambient);

        /// \brief Gets the diffuse coefficient
        /// \return The diffuse coefficient, between 0 and 1
        NODISCARD double get_diffuse() const;

        /// \brief Sets the diffuse
        /// \param diffuse The diffuse coefficient
        /// \note If the diffuse coefficient is less than 0, it will be set to 0
        /// \note If the diffuse coefficient is greater than 1, it will be set to 1
        /// \example material.set_diffuse(0.5); -> diffuse = 0.5
        /// \example material.set_diffuse(1.8); -> diffuse = 1
        void set_diffuse(double diffuse);

        /// \brief Gets the specular coefficient
        /// \return The specular coefficient, between 0 and 1
        NODISCARD double get_specular() const;

        /// \brief Sets the specular coefficient
        /// \param specular The specular coefficient
        /// \note If the specular coefficient is less than 0, it will be set to 0
        /// \note If the specular coefficient is greater than 1, it will be set to 1
        /// \example material.set_specular(0.5); -> specular = 0.5
        /// \example material.set_specular(1.8); -> specular = 1
        void set_specular(double specular);

        /// \brief Gets the shininess coefficient
        /// \return The shininess coefficient, between 1 and infinity
        NODISCARD double get_shininess() const;

        /// \brief Sets the shininess coefficient
        /// \param shininess The shininess coefficient
        /// \note If the shininess coefficient is less than 1, it will be set to 1
        /// \example material.set_shininess(0.5); -> shininess = 1
        /// \example material.set_shininess(50); -> shininess = 50
        void set_shininess(double shininess);

        /// \brief Check if two materials are equal
        /// \param material The material to compare with
        /// \return True if the materials are equal, false otherwise
        NODISCARD bool operator==(const bardrix::material& material) const noexcept;

        /// \brief Check if two materials are different
        /// \param material The material to compare with
        /// \return True if the materials are different, false otherwise
        NODISCARD bool operator!=(const bardrix::material& material) const noexcept;
    };

    /// \brief Bounding Box, used as acceleration structures
    class bounding_box {

    private:
        /// \brief Minimum point of the bounding box
        bardrix::point3 min_;

        /// \brief Maximum point of the bounding box
        bardrix::point3 max_;

    public:
        /// \brief Constructor to create a bounding box
        /// \param min The minimum point of the bounding box
        /// \param max The maximum point of the bounding box
        /// \note The minimum point will be the set of smallest values
        /// \note The maximum point will be the set of biggest values
        bounding_box(const bardrix::point3& min, const bardrix::point3& max) noexcept;

        /// \brief Gets the minimum point of the bounding box
        /// \return The minimum point of the bounding box
        NODISCARD const bardrix::point3& get_min() const noexcept;

        /// \brief Gets the maximum point of the bounding box
        /// \return The maximum point of the bounding box
        NODISCARD const bardrix::point3& get_max() const noexcept;

        /// \brief Sets the minimum point of the bounding box
        /// \param min The minimum point to set
        /// \note The minimum point will be the set of smallest values
        /// \note The maximum point will be the set of biggest values
        void set_min_max(const bardrix::point3& min, const bardrix::point3& max) noexcept;

        /// \brief Check if a point is inside the bounding box
        /// \param point The point to check
        /// \return True if the point is inside the bounding box, false otherwise
        NODISCARD bool inside(const bardrix::point3& point) const noexcept;

        /// \brief Check if a bounding box is inside the bounding box
        /// \param box The bounding box to check
        /// \return True if the bounding box is inside the bounding box, false otherwise
        NODISCARD bool inside(const bounding_box& box) const noexcept;

        /// \brief Check if a bounding box intersects the bounding box
        /// \param box The bounding box to check
        /// \return True if the bounding box intersects the bounding box, false otherwise
        /// \note If the bounding boxes are touching, it will return true
        /// \example bounding_box.intersects(bounding_box) -> true
        NODISCARD bool intersects(const bounding_box& box) const noexcept;

        /// \brief Check if a ray hits the bounding box
        /// \param ray The ray to check
        /// \return True if the ray hits the bounding box, false otherwise
        /// \note The ray length is taken into account
        /// \note If the ray is inside the bounding box, it will return true (even at length 0)
        /// \example bounding_box.intersects(ray) -> true
        NODISCARD bool intersects(const bardrix::ray& ray) const noexcept;

        /// \brief Merges two bounding boxes
        /// \param box The bounding box to merge with
        /// \return A reference to the bounding box merged with the other bounding box
        const bounding_box& merge(const bounding_box& box) noexcept;

        /// \brief Merges two bounding boxes
        /// \param box The bounding box to merge with
        /// \return A new bounding box merged with the other bounding box
        NODISCARD bounding_box merged(const bounding_box& box) const noexcept;

        /// \brief Expands the bounding box by a value
        /// \param distance The distance to expand the bounding box by
        /// \return A reference to the bounding box expanded by the value
        /// \note If the value is negative it will shrink the bounding box  \n
        ///       If the value is positive it will expand the bounding box  \n
        /// \note If the box is being shrunk it cannot invert the min and max values
        const bounding_box& expand(double distance) noexcept;

        /// \brief Expands the bounding box by a value
        /// \param distance The distance to expand the bounding box by
        /// \return A new bounding box expanded by the value
        /// \note If the value is negative it will shrink the bounding box  \n
        ///       If the value is positive it will expand the bounding box  \n
        /// \note If the box is being shrunk it cannot invert the min and max values
        NODISCARD bounding_box expanded(double distance) const noexcept;

        /// \brief Check if the bounding box has no volume (min == max)
        /// \return True if the bounding box has no volume, false otherwise
        NODISCARD bool is_empty() const noexcept;

        /// \brief Gets the center of the bounding box
        /// \return The center of the bounding box
        NODISCARD bardrix::point3 center() const noexcept;

        /// \brief Gets the width of the bounding box
        /// \return The width of the bounding box
        NODISCARD double width() const noexcept;

        /// \brief Gets the height of the bounding box
        /// \return The height of the bounding box
        NODISCARD double height() const noexcept;

        /// \brief Gets the depth of the bounding box
        /// \return The depth of the bounding box
        NODISCARD double depth() const noexcept;

        /// \brief Gets the volume of the bounding box
        /// \return The volume of the bounding box
        NODISCARD double volume() const noexcept;

        /// \brief Gets the area of the bounding box
        /// \return The area of the bounding box
        NODISCARD double area() const noexcept;

        /// \brief Gets the diagonal of the bounding box
        /// \return The diagonal of the bounding box
        NODISCARD double diagonal() const noexcept;

        /// \brief Moves the bounding box by a vector
        /// \param vector The vector to move the bounding box by
        /// \return A new bounding box moved by the vector
        /// \example bounding_box + vector3(1, 1, 1) -> bounding_box moved by (1, 1, 1)
        NODISCARD bounding_box operator+(const bardrix::vector3& vector) const noexcept;

        /// \brief Moves the bounding box by a value (x + value, y + value, z + value)
        /// \param value The value to move the bounding box by
        /// \return A new bounding box moved by the value
        /// \example bounding_box + 1 -> bounding_box moved by (1, 1, 1)
        NODISCARD bounding_box operator+(double value) const noexcept;

        /// \brief Moves the bounding box by a vector
        /// \param vector The vector to move the bounding box by
        /// \return A reference to the bounding box moved by the vector
        /// \example bounding_box += vector3(1, 1, 1) -> bounding_box moved by (1, 1, 1)
        const bounding_box& operator+=(const bardrix::vector3& vector) noexcept;

        /// \brief Moves the bounding box by a value (x + value, y + value, z + value)
        /// \param value The value to move the bounding box by
        /// \return A reference to the bounding box moved by the value
        /// \example bounding_box += 1 -> bounding_box moved by (1, 1, 1)
        const bounding_box& operator+=(double value) noexcept;

        /// \brief Moves the bounding box by a vector
        /// \param vector The vector to move the bounding box by
        /// \return A new bounding box moved by the vector
        /// \example bounding_box - vector3(1, 1, 1) -> bounding_box moved by (-1, -1, -1)
        NODISCARD bounding_box operator-(const bardrix::vector3& vector) const noexcept;

        /// \brief Moves the bounding box by a value (x - value, y - value, z - value)
        /// \param value The value to move the bounding box by
        /// \return A new bounding box moved by the value
        /// \example bounding_box - 1 -> bounding_box moved by (-1, -1, -1)
        NODISCARD bounding_box operator-(double value) const noexcept;

        /// \brief Moves the bounding box by a vector
        /// \param vector The vector to move the bounding box by
        /// \return A reference to the bounding box moved by the vector
        /// \example bounding_box -= vector3(1, 1, 1) -> bounding_box moved by (-1, -1, -1)
        const bounding_box& operator-=(const bardrix::vector3& vector) noexcept;

        /// \brief Moves the bounding box by a value (x - value, y - value, z - value)
        /// \param value The value to move the bounding box by
        /// \return A reference to the bounding box moved by the value
        /// \example bounding_box -= 1 -> bounding_box moved by (-1, -1, -1)
        const bounding_box& operator-=(double value) noexcept;

        /// \brief Check if two bounding boxes are equal
        /// \param box The bounding box to compare with
        /// \return True if the bounding boxes are equal, false otherwise
        NODISCARD bool operator==(const bounding_box& box) const noexcept;

        /// \brief Check if two bounding boxes are different
        /// \param box The bounding box to compare with
        /// \return True if the bounding boxes are different, false otherwise
        NODISCARD bool operator!=(const bounding_box& box) const noexcept;

        /// \brief Displays the bounding box to an output stream
        /// \param os The output stream to display the bounding box to
        /// \param box The bounding box to display
        /// \return The output stream
        friend std::ostream& operator<<(std::ostream& os, const bounding_box& box);

    }; // class bounding_box

    /// \brief A pure virtual class for a 3D shape
    /// \details This class represents a 3D shape, such as a sphere or a plane
    /// \note This is but a base class, it can be inherited to create more complex materials
    class shape {
    public:
        /// \brief Sets the position of the shape
        /// \param position The position to set
        virtual void set_position(const bardrix::point3& position) = 0;

        /// \brief Gets the position of the shape
        /// \return The position of the shape
        NODISCARD virtual const bardrix::point3& get_position() const = 0;

        /// \brief Sets the material of the shape
        /// \param material The material to set
        virtual void set_material(const bardrix::material& material) = 0;

        /// \brief Gets the material of the shape
        /// \return The material of the shape
        NODISCARD virtual const bardrix::material& get_material() const = 0;

        /// \brief Intersection of a ray with the shape
        /// \param ray The ray to intersect with
        /// \return The intersection point, if any
        NODISCARD virtual std::optional<bardrix::point3> intersection(const bardrix::ray& ray) const = 0;

        /// \brief Gets the normal of the shape at a point
        /// \param point The point to get the normal at
        /// \return The normal of the shape at the point
        NODISCARD virtual bardrix::vector3 normal_at(const bardrix::point3& point) const = 0;

        /// \brief Gets the bounding box of the shape
        /// \return The bounding box of the shape
        NODISCARD virtual bardrix::bounding_box bounding_box() const = 0;

        /// \brief Virtual destructor for shape
        virtual ~shape() = default;

    }; // class shape

    /// \brief Sphere shape
    class sphere : public bardrix::shape {
    protected:
        /// \brief Center of the sphere
        bardrix::point3 position_;

        // \brief Material of the sphere
        bardrix::material material_;

        /// \brief Radius of the sphere
        double radius_;

    public:
        /// \brief Default constructor for sphere (radius = 1, position = {0, 0, 0}, material = (color = white, ambient = 0, diffuse = 1, specular = 0, shininess = 0))
        sphere();

        /// \brief Constructor for sphere (position = {0, 0, 0}, material = (color = white, ambient = 0, diffuse = 1, specular = 0, shininess = 0))
        /// \param radius The radius of the sphere
        explicit sphere(double radius);

        /// \brief Constructor for sphere (material (color = white, ambient = 0, diffuse = 1, specular = 0, shininess = 0))
        /// \param position The position of the sphere
        /// \param radius The radius of the sphere
        sphere(const bardrix::point3& position, double radius);

        /// \brief Constructor for sphere
        /// \param position The position of the sphere
        /// \param material The material of the sphere
        /// \param radius The radius of the sphere
        sphere(bardrix::point3 position, const bardrix::material& material, double radius);

        /// \brief Gets the material of the sphere
        /// \return The material of the sphere
        NODISCARD const bardrix::material& get_material() const override;

        /// \brief Gets the radius of the sphere
        /// \return The radius of the sphere
        NODISCARD const double& get_radius() const;

        /// \brief Gets the position of the sphere
        /// \return The position of the sphere
        NODISCARD const bardrix::point3& get_position() const override;

        /// \brief Sets the material of the sphere
        /// \param material The material to set
        void set_material(const bardrix::material& material) override;

        /// \brief Sets the radius of the sphere
        /// \param radius The radius to set
        /// \note If the radius is less than 0, it will be set to 0
        void set_radius(double radius);

        /// \brief Sets the position of the sphere
        /// \param position The position to set
        void set_position(const bardrix::point3& position) override;

        /// \brief Get the normal at a point on the sphere
        /// \param intersection The point to get the normal at
        /// \return The normal at the point
        /// \example Bardrix::vector3 normal = sphere.normal_at(intersection);
        NODISCARD bardrix::vector3 normal_at(const bardrix::point3& intersection) const override;

        /// \brief Get the intersection point of a ray with the sphere
        /// \param ray The ray to check for intersection
        /// \return The intersection point if it exists, otherwise std::nullopt (this means no intersection)
        /// \example Std::optional<bardrix::point3> intersection = sphere.intersection(ray);
        /// \example If (intersection.has_value()) { /* Do something with the intersection point */ }
        /// \details If the intersection point is inside the sphere, it will return an std::nullopt
        NODISCARD std::optional<bardrix::point3> intersection(const bardrix::ray& ray) const override;

        /// \brief Get the bounding box of the sphere
        /// \return The bounding box of the sphere
        /// \example bardrix::bounding_box box = sphere.bounding_box();
        NODISCARD bardrix::bounding_box bounding_box() const override;

        /// \brief Check if two spheres are equal
        /// \param sphere The sphere to compare with
        /// \return True if the spheres are equal, false otherwise
        NODISCARD bool operator==(const bardrix::sphere& sphere) const noexcept;

        /// \brief Check if two spheres are different
        /// \param sphere The sphere to compare with
        /// \return True if the spheres are different, false otherwise
        NODISCARD bool operator!=(const bardrix::sphere& sphere) const noexcept;

    }; // class sphere

} // namespace bardrix
