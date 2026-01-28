#ifndef __PHYSEKS_CORE_HPP__
#define __PHYSEKS_CORE_HPP__

#include <vector>
#include <list>

#include "vec2.hpp"
#include "geometry.hpp"
#include "bodies.hpp"
#include "force.hpp"

namespace phy 
{

    class Physeks {

        std::list<PhyseksBody> allBodies;

        public:
            AABB boundary;

            Physeks() = default;
            void createWorldBound(const vec2& pos, const vec2& size);

            PhyseksBody* addObject(const PhyseksBody& body);

            decltype(allBodies)& getBodies();
            bool update(const float& dt);

        private:
            void integratePosition(const float& dt);
            void calculateForce(PhyseksBody& body, const float& dt);
            void integrateVelocity(const float& dt);

            void resolveBoundaryBounce(PhyseksBody& body, const float& dt);
    };

}

#endif 