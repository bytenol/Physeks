// #include "../include/physeks/core.hpp"



// void phy::Physeks::createWorldBound(const vec2 &pos, const vec2 &size)
// {
//     boundary.pos = pos;
//     boundary.size = size;
// }

// phy::PhyseksBody* phy::Physeks::addObject(const PhyseksBody &body)
// {
//     allBodies.push_back(body);
//     return &allBodies.back();
// }


// decltype(phy::Physeks::allBodies) &phy::Physeks::getBodies()
// {
//     return allBodies;
// }



// bool phy::Physeks::update(const float &dt)
// {
//     integratePosition(dt);
//     // calculateForce(dt);
//     // integrateVelocity(dt);

//     return true;
// }


// void phy::Physeks::integratePosition(const float& dt)
// {
//     for(auto it = allBodies.begin(); it != allBodies.end(); it++)
//     {
//         it->pos.x += it->vel.x * dt;
//         it->pos.y += it->vel.y * dt;

//         if(it->boundaryConstraint) {
//             resolveBoundaryBounce(*it, dt);
//         }
//     }
// }


// void phy::Physeks::resolveBoundaryBounce(PhyseksBody& body, const float& dt)
// {
//     if(body.type == BodyTypeEnum::PARTICLE)
//     {
//         auto b = reinterpret_cast<Particle*>(&body);
//         if(b->pos.x - b->radius < boundary.pos.x) {
//             body.pos.x = boundary.pos.x + b->radius;
//             body.vel.x *= -1;
//         }

//         if(b->pos.x + b->radius > boundary.pos.x + boundary.size.x) {
//             body.pos.x = boundary.pos.x + boundary.size.x - b->radius;
//             body.vel.x *= -1;
//         }

//         if(b->pos.y - b->radius < boundary.pos.y) {
//             body.pos.y = boundary.pos.y + b->radius;
//             body.vel.y *= -1;
//         }

//         if(b->pos.y + b->radius > boundary.pos.y + boundary.size.y) {
//             body.pos.y = boundary.pos.y + boundary.size.y - b->radius;
//             body.vel.y *= -1;
//         }
//     }
// }