//
// Created by Bardio on 29/03/2024.
//

#include <bardrix/color.h>

namespace bardrix {

    color::color(unsigned int rgba) : c_union_{ rgba } {}

    color::color(color::uchar r, color::uchar g, color::uchar b, color::uchar a) : c_union_{ r, g, b, a } {}

    color color::operator+(const color& other) const noexcept {
        color result = *this;
        result += other;
        return result;
    }

    color color::operator+(color::uchar scalar) const noexcept {
        color result = *this;
        result += scalar;
        return result;
    }

    color operator+(color::uchar scalar, const color& color) noexcept {
        return color + scalar;
    }

    color& color::operator+=(const color& other) noexcept {
        c_union_.r_g_b_a.r = c_union_.r_g_b_a.r <= UCHAR_MAX - other.c_union_.r_g_b_a.r ? c_union_.r_g_b_a.r +
                                                                                          other.c_union_.r_g_b_a.r
                                                                                        : UCHAR_MAX;
        c_union_.r_g_b_a.g = c_union_.r_g_b_a.g <= UCHAR_MAX - other.c_union_.r_g_b_a.g ? c_union_.r_g_b_a.g +
                                                                                          other.c_union_.r_g_b_a.g
                                                                                        : UCHAR_MAX;
        c_union_.r_g_b_a.b = c_union_.r_g_b_a.b <= UCHAR_MAX - other.c_union_.r_g_b_a.b ? c_union_.r_g_b_a.b +
                                                                                          other.c_union_.r_g_b_a.b
                                                                                        : UCHAR_MAX;
        c_union_.r_g_b_a.a = c_union_.r_g_b_a.a <= UCHAR_MAX - other.c_union_.r_g_b_a.a ? c_union_.r_g_b_a.a +
                                                                                          other.c_union_.r_g_b_a.a
                                                                                        : UCHAR_MAX;
        return *this;
    }

    color& color::operator+=(color::uchar scalar) noexcept {
        c_union_.r_g_b_a.r = c_union_.r_g_b_a.r <= UCHAR_MAX - scalar ? c_union_.r_g_b_a.r + scalar : UCHAR_MAX;
        c_union_.r_g_b_a.g = c_union_.r_g_b_a.g <= UCHAR_MAX - scalar ? c_union_.r_g_b_a.g + scalar : UCHAR_MAX;
        c_union_.r_g_b_a.b = c_union_.r_g_b_a.b <= UCHAR_MAX - scalar ? c_union_.r_g_b_a.b + scalar : UCHAR_MAX;
        c_union_.r_g_b_a.a = c_union_.r_g_b_a.a <= UCHAR_MAX - scalar ? c_union_.r_g_b_a.a + scalar : UCHAR_MAX;
        return *this;
    }

    color color::operator-(const color& other) const noexcept {
        color result = *this;
        result -= other;
        return result;
    }

    color color::operator-(color::uchar scalar) const noexcept {
        color result = *this;
        result -= scalar;
        return result;
    }

    color operator-(color::uchar scalar, const color& color) noexcept {
        return { static_cast<color::uchar>(scalar >= color.c_union_.r_g_b_a.r ? scalar - color.c_union_.r_g_b_a.r : 0),
                 static_cast<color::uchar>(scalar >= color.c_union_.r_g_b_a.g ? scalar - color.c_union_.r_g_b_a.g : 0),
                 static_cast<color::uchar>(scalar >= color.c_union_.r_g_b_a.b ? scalar - color.c_union_.r_g_b_a.b : 0),
                 static_cast<color::uchar>(scalar >= color.c_union_.r_g_b_a.a ? scalar - color.c_union_.r_g_b_a.a
                                                                              : 0) };
    }

    color& color::operator-=(const color& other) noexcept {
        c_union_.r_g_b_a.r =
                c_union_.r_g_b_a.r >= other.c_union_.r_g_b_a.r ? c_union_.r_g_b_a.r - other.c_union_.r_g_b_a.r : 0;
        c_union_.r_g_b_a.g =
                c_union_.r_g_b_a.g >= other.c_union_.r_g_b_a.g ? c_union_.r_g_b_a.g - other.c_union_.r_g_b_a.g : 0;
        c_union_.r_g_b_a.b =
                c_union_.r_g_b_a.b >= other.c_union_.r_g_b_a.b ? c_union_.r_g_b_a.b - other.c_union_.r_g_b_a.b : 0;
        c_union_.r_g_b_a.a =
                c_union_.r_g_b_a.a >= other.c_union_.r_g_b_a.a ? c_union_.r_g_b_a.a - other.c_union_.r_g_b_a.a : 0;
        return *this;
    }

    color& color::operator-=(color::uchar scalar) noexcept {
        c_union_.r_g_b_a.r = c_union_.r_g_b_a.r >= scalar ? c_union_.r_g_b_a.r - scalar : 0;
        c_union_.r_g_b_a.g = c_union_.r_g_b_a.g >= scalar ? c_union_.r_g_b_a.g - scalar : 0;
        c_union_.r_g_b_a.b = c_union_.r_g_b_a.b >= scalar ? c_union_.r_g_b_a.b - scalar : 0;
        c_union_.r_g_b_a.a = c_union_.r_g_b_a.a >= scalar ? c_union_.r_g_b_a.a - scalar : 0;
        return *this;
    }

    color color::operator*(const double scalar) const noexcept {
        color result = *this;
        result *= scalar;
        return result;
    }

    color operator*(const double scalar, const color& color) noexcept {
        return color * scalar;
    }

    color& color::operator*=(const double scalar) noexcept {
        if (less_than_or_nearly_equal(scalar, 0))
            this->c_union_ = { 0, 0, 0, 0 };

        c_union_.r_g_b_a.r = static_cast<color::uchar>(c_union_.r_g_b_a.r * scalar <= UCHAR_MAX ? c_union_.r_g_b_a.r *
                                                                                                  scalar : UCHAR_MAX);
        c_union_.r_g_b_a.g = static_cast<color::uchar>(c_union_.r_g_b_a.g * scalar <= UCHAR_MAX ? c_union_.r_g_b_a.g *
                                                                                                  scalar : UCHAR_MAX);
        c_union_.r_g_b_a.b = static_cast<color::uchar>(c_union_.r_g_b_a.b * scalar <= UCHAR_MAX ? c_union_.r_g_b_a.b *
                                                                                                  scalar : UCHAR_MAX);
        c_union_.r_g_b_a.a = static_cast<color::uchar>(c_union_.r_g_b_a.a * scalar <= UCHAR_MAX ? c_union_.r_g_b_a.a *
                                                                                                  scalar : UCHAR_MAX);
        return *this;
    }

    color color::operator/(const double scalar) const {
        if (less_than_or_nearly_equal(scalar, 0))
            throw std::invalid_argument("Division by zero");

        color result = *this;
        result /= scalar;
        return result;
    }

    color operator/(const double scalar, const color& color) {
        if (color.c_union_.rgba == 0 || less_than_or_nearly_equal(scalar, 0))
            throw std::invalid_argument("Division by zero");

        return { static_cast<color::uchar>(scalar / color.c_union_.r_g_b_a.r <= UCHAR_MAX ? scalar /
                                                                                            color.c_union_.r_g_b_a.r
                                                                                          : UCHAR_MAX),
                 static_cast<color::uchar>(scalar / color.c_union_.r_g_b_a.g <= UCHAR_MAX ? scalar /
                                                                                            color.c_union_.r_g_b_a.g
                                                                                          : UCHAR_MAX),
                 static_cast<color::uchar>(scalar / color.c_union_.r_g_b_a.b <= UCHAR_MAX ? scalar /
                                                                                            color.c_union_.r_g_b_a.b
                                                                                          : UCHAR_MAX),
                 static_cast<color::uchar>(scalar / color.c_union_.r_g_b_a.a <= UCHAR_MAX ? scalar /
                                                                                            color.c_union_.r_g_b_a.a
                                                                                          : UCHAR_MAX) };
    }

    color& color::operator/=(const double scalar) {
        if (less_than_or_nearly_equal(scalar, 0))
            throw std::invalid_argument("Division by zero");

        c_union_.r_g_b_a.r = static_cast<color::uchar>(c_union_.r_g_b_a.r / scalar <= UCHAR_MAX ? c_union_.r_g_b_a.r /
                                                                                                  scalar : UCHAR_MAX);
        c_union_.r_g_b_a.g = static_cast<color::uchar>(c_union_.r_g_b_a.g / scalar <= UCHAR_MAX ? c_union_.r_g_b_a.g /
                                                                                                  scalar : UCHAR_MAX);
        c_union_.r_g_b_a.b = static_cast<color::uchar>(c_union_.r_g_b_a.b / scalar <= UCHAR_MAX ? c_union_.r_g_b_a.b /
                                                                                                  scalar : UCHAR_MAX);
        c_union_.r_g_b_a.a = static_cast<color::uchar>(c_union_.r_g_b_a.a / scalar <= UCHAR_MAX ? c_union_.r_g_b_a.a /
                                                                                                  scalar : UCHAR_MAX);
        return *this;
    }

    bool color::operator==(const color& other) const noexcept {
        return c_union_.r_g_b_a.r == other.c_union_.r_g_b_a.r && c_union_.r_g_b_a.g == other.c_union_.r_g_b_a.g &&
               c_union_.r_g_b_a.b == other.c_union_.r_g_b_a.b && c_union_.r_g_b_a.a == other.c_union_.r_g_b_a.a;
    }

    bool color::operator!=(const color& other) const noexcept {
        return !(*this == other);
    }

    std::ostream& color::print(std::ostream& os) const noexcept {
     return os << "(" << static_cast<int>(c_union_.r_g_b_a.r) << ", " << static_cast<int>(c_union_.r_g_b_a.g)
               << ", " << static_cast<int>(c_union_.r_g_b_a.b) << ", " << static_cast<int>(c_union_.r_g_b_a.a) << ")";
    }

    std::ostream& operator<<(std::ostream& os, const color& color) noexcept {
        return color.print(os);
    }

} // bardrix