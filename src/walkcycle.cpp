#include "walkcycle.h"
#include "servos.h"
#include <Arduino.h>
#include <cmath>

namespace {

float cycle(float phase) {
    return phase - std::floor(phase);
}

} // namespace

LegAngles legCycle(float phase) {
    return {cycle(phase) - .5f, 0};
}

float walkCycle(float phase) {
    auto step = .1f;

    for (size_t i = 0; i < 6; ++i) {
        auto leg = legCycle(phase + static_cast<float>(i) / 6);
        if (i > 3) {
            leg.flip();
        }

        servos::moveLeg(i, leg);
    }

    usleep(100'000);

    return phase + step;
}
