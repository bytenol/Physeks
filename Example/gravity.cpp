#include <vector>

#include "include/canvas.h"
#include <physeks/physeks.hpp>


struct Window: public canvas {

    phy::Physeks physeks;
    std::vector<SDL_Color> colors;
    phy::Particle *sun, *earth;

    const float G = 6.67 * 10e-11;

    public:
        Window(const std::string& title): canvas(title){}

    private:
        bool process(const float& dt) override
        {
            return true;
        }

        bool physicsProcess(const float& dt) override 
        {   
            earth->addForce(phy::Force::gravity(earth, sun, G));
            physeks.update(dt);
            return true;
        }


        bool render(SDL_Renderer* renderer) override
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            int i = 0;
            for(auto it = physeks.begin(); it != physeks.end(); it++)
            {
                auto& color = colors[i];
                auto obj = dynamic_cast<phy::Particle*>(it->get());
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
                drawFilledCircle(renderer, obj->pos.x, obj->pos.y, obj->radius);
                i++;
            }

            return true;
        }

        bool init() override {
            setFixedTimeStep(1.0f / 360.0f);
            physeks.createWorldBound(phy::vec2{ 0, 0 }, phy::vec2{ (float)W, (float)H });

            sun = &physeks.createBody<phy::Particle>(60.0f);
            sun->pos = phy::vec2{ 320, 250 };
            sun->useGravity = false;
            // sun->isStatic = true;

            earth = &physeks.createBody<phy::Particle>(15.0f);
            earth->pos = phy::vec2{ 450, 150 };
            earth->mass = 0.1f;
            earth->useGravity = false;
            earth->boundaryConstraint = false;
            earth->vel = phy::vec2{ 10, 30 };

            auto r = sun->pos - earth->pos;
            sun->mass = (50 * 50 * r.length()) / (2 * G);

            colors.push_back(SDL_Color{ 255, 204, 51 });
            colors.push_back(SDL_Color{ 30, 90, 200  });

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
    Window win{ "Gravity" };
    if(!win.start()) return -1;
    return 0;
}