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
    return LegAngles{cycle(phase) - .5f, 0.f};
}

float walkCycle(float phase) {
    auto step = .01f;

    for (size_t i = 0; i < 3; ++i) {
        auto leg1 = legCycle(phase + static_cast<float>(i) / 6.f);
        auto leg2 = legCycle(phase + static_cast<float>(i) / 6.f + 1.f / 3.f);

        servos::moveLeg(i, 0, leg1);
        servos::moveLeg(i, 1, leg2);
    }

    usleep(1000 * step);

    return phase + step;
}
