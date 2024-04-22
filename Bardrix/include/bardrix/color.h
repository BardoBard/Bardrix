//
// Created by Bardio on 29/03/2024.
//

#pragma once

#include <bardrix/bardrix.h>

namespace bardrix {
    /// \brief
    /// A color class that represents a color with red, green, blue and alpha components.
    /// The color can be represented as an unsigned integer, where r g b a are the starting bytes respectively, AABBCCDD -> r = DD, g = CC, b = BB, a = AA.
    /// \note The color components are unsigned.
    class color {
    public:
        NODISCARD INLINE static color white() noexcept { return { 255, 255, 255, 255 }; }

        NODISCARD INLINE static color black() noexcept { return { 0, 0, 0, 255 }; }

        NODISCARD INLINE static color red() noexcept { return { 255, 0, 0, 255 }; }

        NODISCARD INLINE static color green() noexcept { return { 0, 255, 0, 255 }; }

        NODISCARD INLINE static color blue() noexcept { return { 0, 0, 255, 255 }; }

        NODISCARD INLINE static color yellow() noexcept { return { 255, 255, 0, 255 }; }

        NODISCARD INLINE static color cyan() noexcept { return { 0, 255, 255, 255 }; }

        NODISCARD INLINE static color magenta() noexcept { return { 255, 0, 255, 255 }; }

    private:
        typedef unsigned char uchar;

        /// \brief A union to represent the color as an unsigned integer or as separate components.
        /// \note This way we can access the color as a whole or as separate components.
        union color_union {
        public:
            struct {
                uchar r, g, b, a;
            } r_g_b_a;
            unsigned rgba;

            color_union() : rgba{ 0 } {}

            color_union(uchar r, uchar g, uchar b, uchar a) : r_g_b_a{ r, g, b, a } {}

            explicit color_union(unsigned rgba) : rgba{ rgba } {}
        };

    private:
        color_union c_union_{};

    public:
        /// \brief Construct a color with all components set to zero (black).
        color() = default;

        /// \brief Construct a color from red, green, blue and alpha components.
        /// \param r The red component of the color.
        /// \param g The green component of the color.
        /// \param b The blue component of the color.
        /// \param a The alpha component of the color.
        color(uchar r, uchar g, uchar b, uchar a);

        /// \brief Construct a color from an unsigned integer.
        /// \param rgba The color as an unsigned integer.
        /// \note The color is represented as an unsigned integer, where r g b a are the starting bytes respectively, AABBCCDD -> r = DD, g = CC, b = BB, a = AA.
        explicit color(unsigned rgba);


        /// \brief Get the red component of the color.
        /// \return The red component of the color.
        NODISCARD uchar r() const noexcept { return c_union_.r_g_b_a.r; }

        /// \brief Get the green component of the color.
        /// \return The green component of the color.
        NODISCARD uchar g() const noexcept { return c_union_.r_g_b_a.g; }

        /// \brief Get the blue component of the color.
        /// \return The blue component of the color.
        NODISCARD uchar b() const noexcept { return c_union_.r_g_b_a.b; }

        /// \brief Get the alpha component of the color.
        /// \return The alpha component of the color.
        NODISCARD uchar a() const noexcept { return c_union_.r_g_b_a.a; }

        /// \brief Set the red component of the color.
        /// \param r The red component of the color.
        void r(uchar r) noexcept { c_union_.r_g_b_a.r = r; }

        /// \brief Set the green component of the color.
        /// \param g The green component of the color.
        void g(uchar g) noexcept { c_union_.r_g_b_a.g = g; }

        /// \brief Set the blue component of the color.
        /// \param b The blue component of the color.
        void b(uchar b) noexcept { c_union_.r_g_b_a.b = b; }

        /// \brief Set the alpha component of the color.
        /// \param a The alpha component of the color.
        void a(uchar a) noexcept { c_union_.r_g_b_a.a = a; }

        /// \brief Get the color as an unsigned integer.
        /// \return The color as an unsigned integer.
        NODISCARD unsigned rgba() const noexcept { return c_union_.rgba; }

        /// \brief Set the color as an unsigned integer.
        /// \param rgba The color as an unsigned integer.
        void rgba(unsigned rgba) noexcept { c_union_.rgba = rgba; }

        /// \brief Add two colors.
        /// \param other The color to add.
        /// \return The result of the addition as a copy.
        /// \note The result is clamped to the minimum and maximum values of the color.
        NODISCARD color operator+(const color& other) const noexcept;

        /// \brief Add a scalar to the color.
        /// \param scalar The scalar to add.
        /// \return The result of the addition as a copy.
        /// \note The result is clamped to the minimum and maximum values of the color.
        NODISCARD color operator+(uchar scalar) const noexcept;

        /// \brief Add a scalar to the color.
        /// \param scalar The scalar to add.
        /// \param color The color to be added to the scalar.
        /// \return The result of the addition as a copy.
        /// \note The result is clamped to the minimum and maximum values of the color.
        friend color operator+(uchar scalar, const color& color) noexcept;

        /// \brief Add a color to the current color.
        /// \param other The color to add.
        /// \return The current color after the addition, by reference.
        /// \note The result is clamped to the minimum and maximum values of the color.
        color& operator+=(const color& other) noexcept;

        /// \brief Add a scalar to the current color.
        /// \param scalar The scalar to add.
        /// \return The current color after the addition, by reference.
        /// \note The result is clamped to the minimum and maximum values of the color.
        color& operator+=(uchar scalar) noexcept;

        /// \brief Subtract two colors.
        /// \param other The color to subtract.
        /// \return The result of the subtraction as a copy.
        /// \note The result is clamped to the minimum and maximum values of the color.
        NODISCARD color operator-(const color& other) const noexcept;

        /// \brief Subtract a scalar from the color.
        /// \param scalar The scalar to subtract.
        /// \return The result of the subtraction as a copy.
        /// \note The result is clamped to the minimum and maximum values of the color.
        NODISCARD color operator-(uchar scalar) const noexcept;

        /// \brief Subtract a scalar from the color.
        /// \param scalar The scalar to subtract.
        /// \param color The color to be subtracted from the scalar.
        /// \return The result of the subtraction as a copy.
        /// \note The result is clamped to the minimum and maximum values of the color.
        friend color operator-(uchar scalar, const color& color) noexcept;

        /// \brief Subtract a color from the current color.
        /// \param other The color to subtract.
        /// \return The current color after the subtraction, by reference.
        /// \note The result is clamped to the minimum and maximum values of the color.
        color& operator-=(const color& other) noexcept;

        /// \brief Subtract a scalar from the current color.
        /// \param scalar The scalar to subtract.
        /// \return The current color after the subtraction, by reference.
        /// \note The result is clamped to the minimum and maximum values of the color.
        color& operator-=(uchar scalar) noexcept;

        /// \brief Multiply the color by a scalar.
        /// \param scalar The scalar to multiply by.
        /// \return The result of the multiplication as a copy.
        /// \note The result is clamped to the minimum and maximum values of the color.
        NODISCARD color operator*(double scalar) const noexcept;

        /// \brief Multiply a scalar by the color.
        /// \param scalar The scalar to multiply by.
        /// \param color The color to be multiplied by the scalar.
        /// \return The result of the multiplication as a copy.
        /// \note The result is clamped to the minimum and maximum values of the color.
        friend color operator*(double scalar, const color& color) noexcept;

        /// \brief Multiply the current color by a scalar.
        /// \param scalar The scalar to multiply by.
        /// \return The current color after the multiplication, by reference.
        /// \note The result is clamped to the minimum and maximum values of the color.
        color& operator*=(double scalar) noexcept;

        /// \brief Divide the color by a scalar.
        /// \param scalar The scalar to divide by.
        /// \return The result of the division as a copy.
        /// \throws std::invalid_argument if the scalar is zero or less.
        /// \note The result is clamped to the minimum and maximum values of the color.
        NODISCARD color operator/(double scalar) const;

        /// \brief Divide a scalar by the color.
        /// \param scalar The scalar to divide by.
        /// \param color The color to be divided by the scalar.
        /// \return The result of the division as a copy.
        /// \throws std::invalid_argument if any of the elements of color are 0.
        /// \throws std::invalid_argument if the scalar is less than 0.
        /// \note The result is clamped to the minimum and maximum values of the color.
        friend color operator/(double scalar, const color& color);

        /// \brief Divide the current color by a scalar.
        /// \param scalar The scalar to divide by.
        /// \return The current color after the division, by reference.
        /// \throws std::invalid_argument if the scalar is zero or less.
        /// \note The result is clamped to the minimum and maximum values of the color.
        color& operator/=(double scalar);

        /// \brief Modulo operation on the color.
        /// \param scalar The scalar to modulo by.
        /// \return The result of the modulo operation as a copy.
        /// \throws std::invalid_argument if the scalar is zero.
        NODISCARD color operator%(uchar scalar) const;

        /// \brief Modulo operation on the color.
        /// \param scalar The scalar to modulo by.
        /// \param color The color to be modulo by the scalar.
        /// \return The result of the modulo operation as a copy.
        /// \throws std::invalid_argument if any of the elements of color are 0.
        friend color operator%(uchar scalar, const color& color);

        /// \brief Modulo operation on the current color.
        /// \param scalar The scalar to modulo by.
        /// \return The current color after the modulo operation, by reference.
        /// \throws std::invalid_argument if the scalar is zero.
        color& operator%=(uchar scalar);

        /// \brief Check if two colors are equal.
        /// \param other The color to compare with.
        /// \return True if the colors are equal, false otherwise.
        /// \example color(255, 255, 255, 255) == color(255, 255, 255, 255) // true
        /// \example color(255, 255, 255, 255) == color(255, 255, 255, 0) // false
        NODISCARD bool operator==(const color& other) const noexcept;

        /// \brief Check if two colors are not equal.
        /// \param other The color to compare with.
        /// \return True if the colors are not equal, false otherwise.
        /// \example color(255, 255, 255, 255) != color(255, 255, 255, 255) // false
        /// \example color(255, 255, 255, 255) != color(255, 255, 255, 0) // true
        NODISCARD bool operator!=(const color& other) const noexcept;

        /// \brief Check if the current color is less than another color.
        /// \param other The color to compare with.
        /// \return True if the current color is less than the other color, false otherwise.
        /// \example color(0, 0, 0, 0) < color(255, 255, 255, 255) // true
        NODISCARD bool operator<(const color& other) const noexcept;

        /// \brief Check if the current color is less than or equal to another color.
        /// \param other The color to compare with.
        /// \return True if the current color is less than or equal to the other color, false otherwise.
        /// \example color(0, 0, 0, 0) <= color(255, 255, 255, 255) // true
        NODISCARD bool operator<=(const color& other) const noexcept;

        /// \brief Check if the current color is greater than another color.
        /// \param other The color to compare with.
        /// \return True if the current color is greater than the other color, false otherwise.
        /// \example color(255, 255, 255, 255) > color(0, 0, 0, 0) // true
        NODISCARD bool operator>(const color& other) const noexcept;

        /// \brief Check if the current color is greater than or equal to another color.
        /// \param other The color to compare with.
        /// \return True if the current color is greater than or equal to the other color, false otherwise.
        /// \example color(255, 255, 255, 255) >= color(0, 0, 0, 0) // true
        NODISCARD bool operator>=(const color& other) const noexcept;

        /// \brief Print the color to an output stream.
        /// \param os The output stream to print to.
        /// \return The output stream after printing the color.
        std::ostream& print(std::ostream& os) const noexcept;

        /// \brief Print the color to an output stream.
        /// \param os The output stream to print to.
        /// \param color The color to print.
        /// \return The output stream after printing the color.
        /// \example std::cout << color(255, 255, 255, 255); // (255, 255, 255, 255)
        friend std::ostream& operator<<(std::ostream& os, const color& color) noexcept;
    };

} // bardrix
