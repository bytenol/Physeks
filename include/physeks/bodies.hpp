#ifndef __PHYSEKS_PARTICLE_HPP__
#define __PHYSEKS_PARTICLE_HPP__

#include <vector>
#include "vec2.hpp"

namespace phy
{

    enum class BodyTypeEnum 
    {
        DEFAULT, 
        PARTICLE
    };

    struct PhyseksBody 
    {
        vec2 pos, vel, acc, force;

        BodyTypeEnum type = BodyTypeEnum::DEFAULT;

        float mass = 1.0f;
        float g = 10.0f;
        bool useGravity = true;
        bool boundaryConstraint = true;

        void calcForces();

        private:
            vec2 lastPos, lastVel, lastAcc, lastForce;
            std::vector<vec2> forces;
    };


    struct Particle: public PhyseksBody
    {
        bool charge = 0.0f;
        float radius = 10.0f;

        Particle()
        {
            type = BodyTypeEnum::PARTICLE;
        }
    };
    
}

#endif 