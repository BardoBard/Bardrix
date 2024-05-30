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
    };

    /// \brief A pure virtual class for a 3D shape
    /// \details This class represents a 3D shape, such as a sphere or a plane
    /// \note This is but a base class, it can be inherited to create more complex materials
    class shape {
    public:
        /// \brief Gets the position of the shape
        /// \return The position of the shape
        NODISCARD virtual const bardrix::point3& get_position() const = 0;

        /// \brief Sets the position of the shape
        /// \param position The position to set
        virtual void set_position(const bardrix::point3& position) = 0;

        /// \brief Intersection of a ray with the shape
        /// \param ray The ray to intersect with
        /// \return The intersection point, if any
        NODISCARD virtual std::optional<bardrix::point3> intersection(const bardrix::ray& ray) const = 0;

        /// \brief Gets the normal of the shape at a point
        /// \param point The point to get the normal at
        /// \return The normal of the shape at the point
        NODISCARD virtual bardrix::vector3 normal_at(const bardrix::point3& point) const = 0;

        /// \brief Gets the material of the shape
        /// \return The material of the shape
        NODISCARD virtual const bardrix::material& get_material() const = 0;

        /// \brief Sets the material of the shape
        /// \param material The material to set
        virtual void set_material(const bardrix::material& material) = 0;

        /// \brief Virtual destructor for shape
        virtual ~shape() = default;

    }; // class shape
} // namespace bardrix
