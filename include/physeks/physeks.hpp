#ifndef __BYTENOL_PHYSEKS_HPP__
#define __BYTENOL_PHYSEKS_HPP__

#include <iostream>
#include <vector>
#include <list>
#include <memory>


namespace phy
{

    struct PhyseksBody;
    struct Physeks;

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

        static vec2 fromAngle(const float& angle, const float& scale = 1.0f);
    };


    struct Force
    {
        static vec2 weight(const float& mass, const float& g);

        static vec2 gravity(PhyseksBody* body1, PhyseksBody* body2, const float& G);
    };


    struct AABB
    {
        vec2 pos, size;
        
    };



    enum class BodyTypeEnum 
    {
        DEFAULT, 
        PARTICLE,
        RIGID_CIRCLE,
        RIGID_POLYGON,
        RIGID_AABB
    };


    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////    Body        Functionalities ////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    struct PhyseksBody 
    {
        friend Physeks;

        vec2 pos, vel;

        BodyTypeEnum type = BodyTypeEnum::DEFAULT;

        float mass = 1.0f;
        float g = 10.0f;
        float bounceFactor = 1.0f;
        bool useGravity = true;
        bool boundaryConstraint = true;
        bool isStatic = false;
        bool isGrounded = false;

        PhyseksBody(): id(ID++) {}

        inline int getId() const 
        {
            return id;
        }

        void addForce(const vec2& force) 
        {
            this->force += force;
        }

        virtual ~PhyseksBody() = default;

        protected:
            virtual void resolveBoundaryConstraint(const AABB& boundary) = 0;

        protected:
            void integratePosition(const float& dt)
            {
                lastPos.x = pos.x;
                lastPos.y = pos.y;
                pos += vel * dt;
            }

            void resolveForces()
            {
                auto weight = Force::weight(mass, useGravity ? g: 0);
                force += weight;
                acc = force * (1 / mass);
                force.x = 0;
                force.y = 0;
            }

            void integrateVelocity(const float& dt)
            {
                lastVel.x = vel.x;
                lastVel.y = vel.y;
                vel += acc * dt;
            }

        private:
            static int ID;
            int id;
            vec2 lastPos, lastVel, acc, force;
    };


    using object_type = PhyseksBody;
    int PhyseksBody::ID = 0;


    struct Particle: public PhyseksBody
    {
        bool charge = 0.0f;
        float radius = 0.0f;

        Particle(float r = 10.0f)
        {
            type = BodyTypeEnum::PARTICLE;
            radius = r;
        }

        private:
            void resolveBoundaryConstraint(const AABB& boundary)
            {
                if(!boundaryConstraint) return;

                isGrounded = false;
                if(pos.x - radius < boundary.pos.x) 
                {
                    pos.x = radius;
                    vel.x *= -bounceFactor;
                } else if(pos.x + radius > boundary.pos.x + boundary.size.x)
                {
                    pos.x = boundary.pos.x + boundary.size.x - radius;
                    vel.x *= -bounceFactor;
                }

                if(pos.y - radius < boundary.pos.y) 
                {
                    pos.y = radius;
                    vel.y *= -bounceFactor;
                } else if(pos.y + radius > boundary.pos.y + boundary.size.y)
                {
                    pos.y = boundary.pos.y + boundary.size.y - radius;
                    vel.y *= -bounceFactor;
                    isGrounded = true;
                }
            }
    };


    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////    Core Engine Functionalities ////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    class Physeks {

        // std::vector<PhyseksBody> allB
        using body_type = std::unique_ptr<PhyseksBody>;
        std::vector<body_type> allBodies;

        public:
            AABB boundary;

            Physeks() = default;

            void update(const float& dt)
            {
                // integrate position
                for(auto& body: allBodies) {
                    if(body->isStatic) continue;
                    body->integratePosition(dt);
                    body->resolveBoundaryConstraint(boundary);
                }

                // force and velocity
                for(auto& body: allBodies) {
                    if(body->isStatic) continue;
                    body->resolveForces();
                    body->integrateVelocity(dt);
                }
            }

            template<typename T, typename... Args>
            T& createBody(Args&&... args) 
            {
                static_assert(std::is_base_of_v<PhyseksBody, T>, "T must derive from PhyseksBody");
                auto body = std::make_unique<T>(std::forward<Args>(args)...);
                T& ref = *body;
                allBodies.push_back(std::move(body));
                return ref;
            }

            void createWorldBound(const vec2& pos, const vec2& size)
            {
                boundary.pos = pos;
                boundary.size = size;
            }

            decltype(allBodies.begin()) begin() {
                return allBodies.begin();
            }

            decltype(allBodies.end()) end() {
                return allBodies.end();
            }
    };



    vec2 vec2::operator+(const vec2 &other) const
    {
        return vec2(x + other.x, y + other.y);
    }


    vec2 vec2::operator-(const vec2 &other) const
    {
        return vec2(x - other.x, y - other.y);
    }


    vec2 vec2::operator*(const float &other) const
    {
        return vec2(x * other, y * other);
    }


    vec2& vec2::operator+=(const vec2 &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    vec2& vec2::operator-=(const vec2 &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }


    vec2& vec2::operator*=(const float &other)
    {
        x *= other;
        y *= other;
        return *this;
    }


    vec2 vec2::normalize() const
    {
        const float l = length();
        if(l == 0) return vec2(0, 0);
        return vec2(x / l, y / l);
    }

    inline float vec2::length() const
    {
        return std::hypot(x, y);
    }


    vec2 vec2::fromAngle(const float& angle, const float& scale)
    {
        return vec2(std::cos(angle) * scale, std::sin(angle) * scale);
    }


    vec2 Force::gravity(PhyseksBody *body1, PhyseksBody *body2, const float &G)
    {
        const auto r = body2->pos - body1->pos;
        const float dist = r.length();
        const float forceMag = (G * body2->mass * body1->mass) / (dist * dist);
        return (r * (1/dist)) * forceMag; 
    }


    vec2 Force::weight(const float& mass, const float& g)
    {
        return vec2(0, mass * g);
    }
   
}

#endif 