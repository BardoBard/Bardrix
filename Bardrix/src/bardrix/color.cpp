//
// Created by Bardio on 29/03/2024.
//

#include <bardrix/color.h>

namespace bardrix {


    color color::operator+(const color& other) const {
        return {static_cast<color::uchar>(c.r_g_b_a.r <= UCHAR_MAX - other.c.r_g_b_a.r ? c.r_g_b_a.r + other.c.r_g_b_a.r : UCHAR_MAX),
                static_cast<color::uchar>(c.r_g_b_a.g <= UCHAR_MAX - other.c.r_g_b_a.g ? c.r_g_b_a.g + other.c.r_g_b_a.g : UCHAR_MAX),
                static_cast<color::uchar>(c.r_g_b_a.b <= UCHAR_MAX - other.c.r_g_b_a.b ? c.r_g_b_a.b + other.c.r_g_b_a.b : UCHAR_MAX),
                static_cast<color::uchar>(c.r_g_b_a.a <= UCHAR_MAX - other.c.r_g_b_a.a ? c.r_g_b_a.a + other.c.r_g_b_a.a : UCHAR_MAX)};
    }

    color color::operator+(color::uchar scalar) const {
        return {static_cast<color::uchar>(c.r_g_b_a.r <= UCHAR_MAX - scalar ? c.r_g_b_a.r + scalar : UCHAR_MAX),
                static_cast<color::uchar>(c.r_g_b_a.g <= UCHAR_MAX - scalar ? c.r_g_b_a.g + scalar : UCHAR_MAX),
                static_cast<color::uchar>(c.r_g_b_a.b <= UCHAR_MAX - scalar ? c.r_g_b_a.b + scalar : UCHAR_MAX),
                static_cast<color::uchar>(c.r_g_b_a.a <= UCHAR_MAX - scalar ? c.r_g_b_a.a + scalar : UCHAR_MAX)};
    }

    color operator+(color::uchar scalar, const color& color) {
        return color + scalar;
    }

    color& color::operator+=(const color& other) {
        c.r_g_b_a.r = c.r_g_b_a.r <= UCHAR_MAX - other.c.r_g_b_a.r ? c.r_g_b_a.r + other.c.r_g_b_a.r : UCHAR_MAX;
        c.r_g_b_a.g = c.r_g_b_a.g <= UCHAR_MAX - other.c.r_g_b_a.g ? c.r_g_b_a.g + other.c.r_g_b_a.g : UCHAR_MAX;
        c.r_g_b_a.b = c.r_g_b_a.b <= UCHAR_MAX - other.c.r_g_b_a.b ? c.r_g_b_a.b + other.c.r_g_b_a.b : UCHAR_MAX;
        c.r_g_b_a.a = c.r_g_b_a.a <= UCHAR_MAX - other.c.r_g_b_a.a ? c.r_g_b_a.a + other.c.r_g_b_a.a : UCHAR_MAX;
        return *this;
    }

    color& color::operator+=(color::uchar scalar) {
        c.r_g_b_a.r = c.r_g_b_a.r <= UCHAR_MAX - scalar ? c.r_g_b_a.r + scalar : UCHAR_MAX;
        c.r_g_b_a.g = c.r_g_b_a.g <= UCHAR_MAX - scalar ? c.r_g_b_a.g + scalar : UCHAR_MAX;
        c.r_g_b_a.b = c.r_g_b_a.b <= UCHAR_MAX - scalar ? c.r_g_b_a.b + scalar : UCHAR_MAX;
        c.r_g_b_a.a = c.r_g_b_a.a <= UCHAR_MAX - scalar ? c.r_g_b_a.a + scalar : UCHAR_MAX;
        return *this;
    }

    color color::operator-(const color& other) const {
        return { static_cast<color::uchar>(c.r_g_b_a.r >= other.c.r_g_b_a.r ? c.r_g_b_a.r - other.c.r_g_b_a.r : 0),
                 static_cast<color::uchar>(c.r_g_b_a.g >= other.c.r_g_b_a.g ? c.r_g_b_a.g - other.c.r_g_b_a.g : 0),
                 static_cast<color::uchar>(c.r_g_b_a.b >= other.c.r_g_b_a.b ? c.r_g_b_a.b - other.c.r_g_b_a.b : 0),
                 static_cast<color::uchar>(c.r_g_b_a.a >= other.c.r_g_b_a.a ? c.r_g_b_a.a - other.c.r_g_b_a.a : 0) };
    }

    color color::operator-(color::uchar scalar) const {
        return { static_cast<color::uchar>(c.r_g_b_a.r >= scalar ? c.r_g_b_a.r - scalar : 0),
                 static_cast<color::uchar>(c.r_g_b_a.g >= scalar ? c.r_g_b_a.g - scalar : 0),
                 static_cast<color::uchar>(c.r_g_b_a.b >= scalar ? c.r_g_b_a.b - scalar : 0),
                 static_cast<color::uchar>(c.r_g_b_a.a >= scalar ? c.r_g_b_a.a - scalar : 0) };
    }

    color operator-(color::uchar scalar, const color& color) {
        return { static_cast<color::uchar>(scalar >= color.c.r_g_b_a.r ? scalar - color.c.r_g_b_a.r : 0),
                 static_cast<color::uchar>(scalar >= color.c.r_g_b_a.g ? scalar - color.c.r_g_b_a.g : 0),
                 static_cast<color::uchar>(scalar >= color.c.r_g_b_a.b ? scalar - color.c.r_g_b_a.b : 0),
                 static_cast<color::uchar>(scalar >= color.c.r_g_b_a.a ? scalar - color.c.r_g_b_a.a : 0) };
    }

    color& color::operator-=(const color& other) {
        c.r_g_b_a.r = c.r_g_b_a.r >= other.c.r_g_b_a.r ? c.r_g_b_a.r - other.c.r_g_b_a.r : 0;
        c.r_g_b_a.g = c.r_g_b_a.g >= other.c.r_g_b_a.g ? c.r_g_b_a.g - other.c.r_g_b_a.g : 0;
        c.r_g_b_a.b = c.r_g_b_a.b >= other.c.r_g_b_a.b ? c.r_g_b_a.b - other.c.r_g_b_a.b : 0;
        c.r_g_b_a.a = c.r_g_b_a.a >= other.c.r_g_b_a.a ? c.r_g_b_a.a - other.c.r_g_b_a.a : 0;
        return *this;
    }

    color& color::operator-=(color::uchar scalar) {
        c.r_g_b_a.r = c.r_g_b_a.r >= scalar ? c.r_g_b_a.r - scalar : 0;
        c.r_g_b_a.g = c.r_g_b_a.g >= scalar ? c.r_g_b_a.g - scalar : 0;
        c.r_g_b_a.b = c.r_g_b_a.b >= scalar ? c.r_g_b_a.b - scalar : 0;
        c.r_g_b_a.a = c.r_g_b_a.a >= scalar ? c.r_g_b_a.a - scalar : 0;
        return *this;
    }

    color color::operator*(color::uchar scalar) const {
        return { static_cast<color::uchar>(c.r_g_b_a.r * scalar / UCHAR_MAX),
                 static_cast<color::uchar>(c.r_g_b_a.g * scalar / UCHAR_MAX),
                 static_cast<color::uchar>(c.r_g_b_a.b * scalar / UCHAR_MAX),
                 static_cast<color::uchar>(c.r_g_b_a.a * scalar / UCHAR_MAX) };
    }

    color operator*(color::uchar scalar, const color& color) {
        return color * scalar;
    }

    color& color::operator*=(color::uchar scalar) {
        c.r_g_b_a.r = c.r_g_b_a.r * scalar / UCHAR_MAX;
        c.r_g_b_a.g = c.r_g_b_a.g * scalar / UCHAR_MAX;
        c.r_g_b_a.b = c.r_g_b_a.b * scalar / UCHAR_MAX;
        c.r_g_b_a.a = c.r_g_b_a.a * scalar / UCHAR_MAX;
        return *this;
    }

    color color::operator/(color::uchar scalar) const {
        return { static_cast<color::uchar>(c.r_g_b_a.r / scalar * UCHAR_MAX),
                 static_cast<color::uchar>(c.r_g_b_a.g / scalar * UCHAR_MAX),
                 static_cast<color::uchar>(c.r_g_b_a.b / scalar * UCHAR_MAX),
                 static_cast<color::uchar>( c.r_g_b_a.a / scalar * UCHAR_MAX) };
    }

    color operator/(color::uchar scalar, const color& color) {
        return { static_cast<color::uchar>(scalar / color.c.r_g_b_a.r * UCHAR_MAX),
                 static_cast<color::uchar>(scalar / color.c.r_g_b_a.g * UCHAR_MAX),
                 static_cast<color::uchar>(scalar / color.c.r_g_b_a.b * UCHAR_MAX),
                 static_cast<color::uchar>(scalar / color.c.r_g_b_a.a * UCHAR_MAX) };
    }

    color& color::operator/=(color::uchar scalar) {
        c.r_g_b_a.r = c.r_g_b_a.r / scalar * UCHAR_MAX;
        c.r_g_b_a.g = c.r_g_b_a.g / scalar * UCHAR_MAX;
        c.r_g_b_a.b = c.r_g_b_a.b / scalar * UCHAR_MAX;
        c.r_g_b_a.a = c.r_g_b_a.a / scalar * UCHAR_MAX;
        return *this;
    }


} // bardrix