//
// Created by Bardio on 29/03/2024.
//

#pragma once

#include <bardrix/bardrix.h>

namespace bardrix {

    class color {
    private:
        typedef unsigned char uchar;

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
        color_union c;

    public:
        color() : c{ 0, 0, 0, 0 } {}

        color(uchar r, uchar g, uchar b, uchar a) : c{ r, g, b, a } {}

        explicit color(unsigned rgba) : c{ 0, 0, 0, 0 } { c.rgba = rgba; }

        color(const color& other) = default;

        NODISCARD uchar r() const { return c.r_g_b_a.r; }

        NODISCARD uchar g() const { return c.r_g_b_a.g; }

        NODISCARD uchar b() const { return c.r_g_b_a.b; }

        NODISCARD uchar a() const { return c.r_g_b_a.a; }

        void r(uchar r) { c.r_g_b_a.r = r; }

        void g(uchar g) { c.r_g_b_a.g = g; }

        void b(uchar b) { c.r_g_b_a.b = b; }

        void a(uchar a) { c.r_g_b_a.a = a; }

        NODISCARD unsigned rgba() const { return c.rgba; }

        void rgba(unsigned rgba) { c.rgba = rgba; }

        NODISCARD color operator+(const color& other) const;

        NODISCARD color operator+(uchar scalar) const;

        friend color operator+(uchar scalar, const color& color);

        color& operator+=(const color& other);

        color& operator+=(uchar scalar);


        NODISCARD color operator-(const color& other) const;

        NODISCARD color operator-(uchar scalar) const;

        friend color operator-(uchar scalar, const color& color);

        color& operator-=(const color& other);

        color& operator-=(uchar scalar);


        NODISCARD color operator*(uchar scalar) const;

        friend color operator*(uchar scalar, const color& color);

        color& operator*=(uchar scalar);

        NODISCARD color operator/(uchar scalar) const;

        friend color operator/(uchar scalar, const color& color);

        color& operator/=(uchar scalar);

        NODISCARD bool operator==(const color& other) const {
            return c.r_g_b_a.r == other.c.r_g_b_a.r && c.r_g_b_a.g == other.c.r_g_b_a.g &&
                   c.r_g_b_a.b == other.c.r_g_b_a.b && c.r_g_b_a.a == other.c.r_g_b_a.a;
        }

        NODISCARD bool operator!=(const color& other) const {
            return c.r_g_b_a.r != other.c.r_g_b_a.r || c.r_g_b_a.g != other.c.r_g_b_a.g ||
                   c.r_g_b_a.b != other.c.r_g_b_a.b || c.r_g_b_a.a != other.c.r_g_b_a.a;
        }
    };

} // bardrix
