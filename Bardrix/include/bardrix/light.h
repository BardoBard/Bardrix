//
// Created by Bardio on 30/03/2024.
//

#pragma once

#include <bardrix/bardrix.h>
#include <bardrix/point3.h>
#include <bardrix/color.h>

namespace bardrix {

    class light {

    public:
        /// \brief The position of the light
        point3 position = point3();

        /// \brief The color of the light
        bardrix::color color = color::white();
    private:
        /// \brief The intensity of the light
        double intensity_ = 1;

    protected:
        /// \brief Calculates the inverse square law squared
        /// \param distance_squared The distance squared
        /// \return The inverse square law squared
        /// \details This method is faster than inverse_square_law, as it does not calculate the square root
        /// \details If the distance squared is 0, the result will be infinity
        NODISCARD double inverse_square_law_squared(double distance_squared) const noexcept;

    public:
        /// \brief Default constructor for light, position (0,0,0), intensity 1, color white
        light() = default;

        /// \brief Constructor for light, initializes position, intensity and color
        /// \param position The position of the light
        /// \param intensity The intensity of the light, must be greater than or equal to 0
        /// \param color The color of the light
        light(point3 position, double intensity, const bardrix::color& color) noexcept;

        /// \brief Get the intensity of the light
        /// \return The intensity of the light
        NODISCARD double get_intensity() const noexcept;

        /// \brief Set the intensity of the light
        /// \param intensity The new intensity of the light
        /// \details If the intensity is less than 0, it will be set to 0
        void set_intensity(double intensity) noexcept;

        /// \brief Calculates the inverse square law
        /// \param point The point to calculate the inverse square law from
        /// \return The inverse square law
        /// \details If the point lies on the light, the result will be infinity
        NODISCARD double inverse_square_law(const point3& point) const noexcept;

        /// \brief Calculates the inverse square law
        /// \param distance The distance to calculate the inverse square law from
        /// \return The inverse square law
        /// \details If the distance is 0, the result will be infinity
        NODISCARD double inverse_square_law(double distance) const noexcept;

        /// \brief Compare two lights
        /// \param other The other light
        /// \return True if the lights are equal
        /// \details Two lights are equal if their position, color and intensity are equal
        /// \example light1 == light2 -> (0,0,0) == (0,0,0) && white == white && 1 == 1 -> true
        NODISCARD bool operator==(const light& other) const noexcept;

        /// \brief Compare two lights
        /// \param other The other light
        /// \return True if the lights are not equal
        /// \details Two lights are not equal if their position, color or intensity are not equal
        /// \example light1 != light2 -> (0,0,0) != (0,0,0) || white != white || 1 != 1 -> false
        NODISCARD bool operator!=(const light& other) const noexcept;

        /// \brief Print the light to an output stream
        /// \param os The output stream
        /// \return The output stream
        std::ostream& print(std::ostream& os) const;

        /// \brief Print the light to an output stream
        /// \param os The output stream
        /// \return The output stream
        /// \example std::cout << light1 -> Light: (0,0,0), Intensity: 1, Color: (255, 255, 255, 255)
        friend std::ostream& operator<<(std::ostream& os, const light& light);

    }; // class light

} // bardrix
