#include "constants.h"
#include "sdlpp/events.hpp"
#include "sdlpp/render.hpp"
#include "sdlpp/window.hpp"
#include "servosim.h"
#include <cmath>
#include <thread>

// Implemented by the actual program
void setup();
void loop();

sdl::Dims screenRect = {400, 400};

void drawCircle(sdl::RendererView renderer, sdl::Point point, float r) {
    auto points = 20;
    for (int i = 0; i <= points; ++i) {
        auto a1 = (pi2f * i) / points;
        auto a2 = (pi2f * (i + 1)) / points;

        renderer.drawLine(point.x + std::sin(a1) * r,
                          point.y + std::cos(a1) * r,
                          point.x + std::sin(a2) * r,
                          point.y + std::cos(a2) * r);
    }
}

void render(sdl::RendererView renderer) {
    renderer.drawColor(0, 0, 0);
    renderer.clear();
    renderer.drawColor(100, 100, 100);

    auto x = screenRect.w / 2;
    auto y = screenRect.h / 2;

    drawCircle(renderer, {x, y}, 50);

    auto &instance = ServoSim::instance();

    for (int i = 0; i < 6; ++i) {
        auto angle = static_cast<float>(i) * pi2f / 6. + pi2f / 12.;
        angle += instance.angles.at(i);
        auto sx = std::sin(angle);
        auto sy = std::cos(angle);

        auto l = 100. + 50 * std::cos(instance.angles.at(i + 6) - pif / 2.);
        renderer.drawLine(x + sx * 40, y + sy * 40, x + sx * l, y + sy * l);
    }

    renderer.present();
}

int main(int argc, char *argv[]) {
    setup();

    bool isRunning = true;

    auto window = sdl::Window{"matpod sim",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              screenRect.w,
                              screenRect.h,
                              0};

    auto renderer = sdl::Renderer{
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC};

    auto thread = std::thread{[&isRunning] {
        while (isRunning) {
            loop();

            // Trigger redraw
            auto refreshEvent = sdl::Event{.type = SDL_USEREVENT};
            sdl::pushEvent(refreshEvent);
        }
    }};

    while (isRunning) {
        if (auto o = sdl::pollEvent()) {
            auto event = *o;
            if (event.type == SDL_QUIT) {
                isRunning = false;
                break;
            }
        }

        ServoSim::instance().update();

        render(renderer);
    }

    thread.join();

    return 0;
}
