#include <vector>

#include "include/canvas.h"
#include <physeks/core.hpp>


struct Window: public canvas {

    phy::Physeks physeks;
    std::vector<SDL_Color> colors;

    public:
        Window(const std::string& title): canvas(title){}

    private:
        bool process(const float& dt) override
        {
            return true;
        }

        bool physicsProcess(const float& dt) override 
        {
            physeks.update(dt);
            return true;
        }


        bool render(SDL_Renderer* renderer) override
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            auto& pBodies = physeks.getBodies();
            int i = 0;
            for(auto it = pBodies.begin(); it != pBodies.end(); it++)
            {
                auto particle = reinterpret_cast<phy::Particle*>(&(*it));
                auto& color = colors[i];
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
                drawFilledCircle(renderer, particle->pos.x, particle->pos.y, particle->radius);

                i++;
            }

            return true;
        }

        bool init() override {
            physeks.createWorldBound(phy::vec2{ 0, 0 }, phy::vec2{ (float)W, (float)H });
            physeks.useGravity = true;

            colors.clear();
            phy::Particle* firstParticle = nullptr;
            for(int i = 0; i < 30; i++) 
            {
                auto particle = reinterpret_cast<phy::Particle*>(physeks.addObject(phy::Particle()));
                particle->pos = phy::vec2{ randRange(50, W - 50), randRange(50, H - 50) };
                particle->radius = randRange(10, 40);
                // particle->vel = phy::vec2{ randRange(-30, 30), randRange(-30, 30) };
                particle->boundaryConstraint = true;
                colors.push_back(SDL_Color{ static_cast<unsigned char>(randRange(0, 255)), static_cast<unsigned char>(randRange(0, 255)), static_cast<unsigned char>(randRange(0, 255)) });

                if(i == 0) firstParticle = particle;                
            }

            // firstParticle->boundaryConstraint = true;


            return true;
        }


        bool inputProcess(SDL_Event& evt) override
        {
            if(evt.type == SDL_EVENT_QUIT) return true;

            return false;
        }

};


int main()
{
    Window win{ "Particles" };
    if(!win.start()) return -1;
    return 0;
}