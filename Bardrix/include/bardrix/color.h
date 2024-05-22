//
// Created by Bardio on 29/03/2024.
//

#pragma once

#include <bardrix/bardrix.h>

namespace bardrix {
    /// \brief
    /// A color class that represents a color with red, green, blue and alpha components.
    /// The color can be represented as an unsigned integer, where r g b a are the starting bytes respectively, RRGGBBAA.
    /// \note The color components are unsigned.
    class color {
    public:
        /// \brief White color (255, 255, 255, 255).
        /// \return The color white.
        NODISCARD INLINE static color white() noexcept { return { 255, 255, 255, 255 }; }

        /// \brief Black color (0, 0, 0, 255).
        /// \return The color black.
        NODISCARD INLINE static color black() noexcept { return { 0, 0, 0, 255 }; }

        /// \brief Red color (255, 0, 0, 255).
        /// \return The color red.
        NODISCARD INLINE static color red() noexcept { return { 255, 0, 0, 255 }; }

        /// \brief Green color (0, 255, 0, 255).
        /// \return The color green.
        NODISCARD INLINE static color green() noexcept { return { 0, 255, 0, 255 }; }

        /// \brief Blue color (0, 0, 255, 255).
        /// \return The color blue.
        NODISCARD INLINE static color blue() noexcept { return { 0, 0, 255, 255 }; }

        /// \brief Yellow color (255, 255, 0, 255).
        /// \return The color yellow.
        NODISCARD INLINE static color yellow() noexcept { return { 255, 255, 0, 255 }; }

        /// \brief Cyan color (0, 255, 255, 255).
        /// \return The color cyan.
        NODISCARD INLINE static color cyan() noexcept { return { 0, 255, 255, 255 }; }

        /// \brief Magenta color (255, 0, 255, 255).
        /// \return The color magenta.
        NODISCARD INLINE static color magenta() noexcept { return { 255, 0, 255, 255 }; }

    protected:
        /// \brief Unsigned char type-definition.
        typedef unsigned char uchar;

        /// \brief A union to represent the color as an unsigned integer or as separate components.
        /// \note This way we can access the color as a whole or as separate components.
        union color_union {
        public:
            /// \brief The color as separate components.
            struct {
                uchar a, b, g, r;
            } r_g_b_a;

            /// \brief The color as a uint32_t; RRGGBBAA.
            uint32_t rgba;

            color_union() : rgba{ 0 } {}

            color_union(uchar r, uchar g, uchar b, uchar a) : r_g_b_a{ a, b, g, r } {}

            explicit color_union(uint32_t rgba) : rgba{ rgba } {}
        };

    protected:
        /// \brief This union represents the color as an unsigned integer or as separate components.
        color_union c_union_{};

    public:
        /// \brief Construct a color with all components set to zero (r: 0, g: 0, b: 0, a: 0).
        color() = default;

        /// \brief Construct a color from red, green, blue and alpha components.
        /// \param r The red component of the color.
        /// \param g The green component of the color.
        /// \param b The blue component of the color.
        /// \param a The alpha component of the color.
        color(uchar r, uchar g, uchar b, uchar a);

        /// \brief Construct a color from a uint32_t.
        /// \param rgba The color as a uint32_t.
        /// \note The color is represented as a uint32_t, where r g b a are the starting bytes respectively, RRGGBBAA.
        explicit color(uint32_t rgba);

        /// \brief Get the red component of the color.
        /// \return The red component of the color.
        NODISCARD uchar r() const noexcept;

        /// \brief Get the green component of the color.
        /// \return The green component of the color.
        NODISCARD uchar g() const noexcept;

        /// \brief Get the blue component of the color.
        /// \return The blue component of the color.
        NODISCARD uchar b() const noexcept;

        /// \brief Get the alpha component of the color.
        /// \return The alpha component of the color.
        NODISCARD uchar a() const noexcept;

        /// \brief Set the red component of the color.
        /// \param r The red component of the color.
        void r(uchar r) noexcept;

        /// \brief Set the green component of the color.
        /// \param g The green component of the color.
        void g(uchar g) noexcept;

        /// \brief Set the blue component of the color.
        /// \param b The blue component of the color.
        void b(uchar b) noexcept;

        /// \brief Set the alpha component of the color.
        /// \param a The alpha component of the color.
        void a(uchar a) noexcept;

        /// \brief Get the color as a uint32_t with format RRGGBBAA.
        /// \return The color as a uint32_t with format RRGGBBAA.
        NODISCARD uint32_t rgba() const noexcept;

        /// \brief Get the color as a uint32_t with format AABBGGRR.
        /// \return The color as a uint32_t with format AABBGGRR.
        NODISCARD uint32_t abgr() const noexcept;

        /// \brief Get the color as a uint32_t with format AARRGGBB.
        /// \return The color as a uint32_t with format AARRGGBB.
        NODISCARD uint32_t argb() const noexcept;

        /// \brief Set the color as a uint32_t with format RRGGBBAA.
        /// \param rgba The color as a uint32_t with format RRGGBBAA.
        void rgba(uint32_t rgba) noexcept;

        /// \brief Set the color as a uint32_t with format AABBGGRR.
        /// \param abgr The color as a uint32_t with format AABBGGRR.
        void abgr(uint32_t abgr) noexcept;

        /// \brief Set the color as a uint32_t with format AARRGGBB.
        /// \param argb The color as a uint32_t with format AARRGGBB.
        void argb(uint32_t argb) noexcept;

        /// \brief Inverts this color.
        /// \details The inversion is calculated as (r,g,b) => (255 - r, 255 - g, 255 - b).
        /// \return A reference to the current color after the inversion.
        /// \example color(255, 0, 0, 255).invert() // (0, 255, 255, 255)
        color& invert() noexcept;

        /// \brief Inverts the color.
        /// \details The inversion is calculated as (r,g,b) => (255 - r, 255 - g, 255 - b).
        /// \return A copy of the color after the inversion.
        /// \example color(255, 0, 0, 255).inverted() // (0, 255, 255, 255)
        NODISCARD color inverted() const noexcept;

        /// \brief Grayscales the color.
        /// \return A reference to the current color after the grayscale.
        /// \details The grayscale is calculated as (r,g,b) => 0.299 * r + 0.587 * g + 0.114 * b.
        /// \example color(255, 0, 0, 255).grayscale() // (76, 76, 76, 255)
        /// \see https://en.wikipedia.org/wiki/Grayscale#Converting_color_to_grayscale
        color& grayscale() noexcept;

        /// \brief Grayscales the color.
        /// \return A copy of the color after the grayscale.
        /// \details The grayscale is calculated as (r,g,b) => 0.299 * r + 0.587 * g + 0.114 * b.
        /// \example color(255, 0, 0, 255).grayscaled() // (76, 76, 76, 255)
        /// \see https://en.wikipedia.org/wiki/Grayscale#Converting_color_to_grayscale
        NODISCARD color grayscaled() const noexcept;

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

        /// \brief Inverts the color; only the r, g, b components are inverted, the alpha component remains the same.
        /// \details The inversion is calculated as (r,g,b) => (255 - r, 255 - g, 255 - b).
        /// \return The inverted color as a copy.
        /// \example ~color(255, 0, 0, 255) // (0, 255, 255, 255)
        NODISCARD color operator~() const noexcept;

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
