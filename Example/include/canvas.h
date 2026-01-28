#ifndef __PHYSEKS_EXAMPLE_CANVAS_H__
#define __PHYSEKS_EXAMPLE_CANVAS_H__

#include <iostream>
#include <string>
#include <chrono>
#include <random>

#include <SDL3/SDL.h>

class canvas {

    static SDL_Window* window;
    static SDL_Renderer* renderer;

    std::string title;
    bool windowShouldClose = false;

    protected:
        static int W, H;
        float physicsStepAccumulator = 0.0f;

    public:

        explicit canvas(const std::string& t, const int& w = 640, const int& h = 480) {
            title = t;

            window = nullptr;
            renderer = nullptr;
            W = w;
            H = h;
        }

        bool start() {
            if(!initSdl3()) return false;

            init();

            SDL_Event evt;
            auto t1 = std::chrono::high_resolution_clock::now().time_since_epoch();

            while (!windowShouldClose) {
                const auto t2 = std::chrono::high_resolution_clock::now().time_since_epoch();
                const float dt = (t2 - t1).count() * 10e-9;
                t1 = t2;

                physicsStepAccumulator += dt;

                while(SDL_PollEvent(&evt))
                    windowShouldClose = inputProcess(evt);

                // regular update
                process(dt);
                // physics update
                while(physicsStepAccumulator >= fixedTimeStep) {
                    physicsProcess(fixedTimeStep);
                    physicsStepAccumulator -= fixedTimeStep;
                }

                render(renderer);
                SDL_RenderPresent(renderer);
            }
        
            return true;
        }

        ~canvas() 
        {
            SDL_DestroyWindow(window);
            SDL_Quit();
        }

    protected:
        virtual bool process(const float& dt) = 0;
        virtual bool render(SDL_Renderer* renderer) = 0;

        virtual bool init() {
            return true;
        };

        virtual bool inputProcess(SDL_Event& evt) {
            return false;
        };

        virtual bool physicsProcess(const float& dt){
            return true;
        };

    protected:

        void setFixedTimeStep(const float& f) 
        {
            fixedTimeStep = f;
        }

        float randRange(const float& min, const float& max)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dist(min, max);
            return dist(gen);
        }

        void drawFilledCircle(SDL_Renderer* r, float px, float py, float radius)
        {
            auto drawHorizontalLine = [](SDL_Renderer* renderer, int x1, int x2, int y) -> void {
                for (int x = x1; x <= x2; x++)
                    SDL_RenderPoint(renderer, x, y);
                };

            int x = 0;
            int y = radius;
            int d = 3 - int(radius) << 1;

            while (y >= x) {
                // Draw horizontal lines (scanlines) for each section of the circle
                drawHorizontalLine(r, px - x, px + x, py - y);
                drawHorizontalLine(r, px - x, px + x, py + y);
                drawHorizontalLine(r, px - y, px + y, py - x);
                drawHorizontalLine(r, px - y, px + y, py + x);

                // Update decision parameter and points
                if (d < 0) {
                    d = d + (x << 2) + 6;
                }
                else {
                    d = d + ((x - y) << 2) + 10;
                    y--;
                }
                x++;

            }
        }



    private:
        float fixedTimeStep = 1.0f / 60.0f;
        bool initSdl3() 
        {
            if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                std::cerr << "SDL_INITIALIZATION_FAILED:: " << SDL_GetError() << std::endl;
                return false;
            }

            const char* _title = title.c_str();
            window = SDL_CreateWindow(_title, W, H, 0);
            renderer = SDL_CreateRenderer(window, nullptr);
            if (!window || !renderer) {
                std::cerr << "WINDOW_CREATION_FAILED:: " << SDL_GetError() << std::endl;
                return false;
            }

            return true;
        }

};


SDL_Window* canvas::window = nullptr;
SDL_Renderer* canvas::renderer = nullptr;
int canvas::W = 640;
int canvas::H = 480;

#endif 