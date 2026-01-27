#ifndef __PHYSEKS_FORCE_HPP__
#define __PHYSEKS_FORCE_HPP__

#include "vec2.hpp"

namespace phy
{
    struct Force
    {
        static vec2 weight(const float& mass, const float& g)
        {
            return vec2(0, mass * g);
        }
    };
}

#endif