#ifndef __PHYSEKS_VEC2_HPP__
#define __PHYSEKS_VEC2_HPP__

#include <cmath>

namespace phy
{
    struct vec2
    {
        float x, y;

        explicit vec2(const float& _x = 0.0f, const float& _y = 0.0f): x(_x), y(_y){};

        vec2 operator+(const vec2& other) const;
        vec2 operator-(const vec2& other) const;
        vec2 operator*(const float& other) const;

        vec2& operator+=(const vec2& other);
        vec2& operator-=(const vec2& other);
        vec2& operator*=(const float& other);

        vec2 normalize() const;
        vec2 perp(const float& scale, const bool& antiClockwise = true) const;

        float dotProduct(const vec2& other) const;
        float crossProduct(const vec2& other) const;

        inline float length() const;

        static vec2 fromAngle(const float& angle);
    };

    inline float vec2::length() const
    {
        return std::hypot(x, y);
    }
}

#endif 