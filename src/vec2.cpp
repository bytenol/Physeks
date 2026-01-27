#include "../include/physeks/vec2.hpp"


using namespace phy;


vec2 phy::vec2::operator+(const vec2 &other) const
{
    return vec2(x + other.x, y + other.y);
}


vec2 phy::vec2::operator-(const vec2 &other) const
{
    return vec2(x - other.x, y - other.y);
}


vec2 phy::vec2::operator*(const float &other) const
{
    return vec2(x * other, y * other);
}


vec2 &phy::vec2::operator+=(const vec2 &other)
{
    x += other.x;
    y += other.y;
    return *this;
}

vec2 &phy::vec2::operator-=(const vec2 &other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}


vec2 &phy::vec2::operator*=(const float &other)
{
    x *= other;
    y *= other;
    return *this;
}


vec2 phy::vec2::normalize() const
{
    const float l = length();
    if(l == 0) return vec2(0, 0);
    return vec2(x / l, y / l);
}

