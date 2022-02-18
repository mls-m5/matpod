#include "servosim.h"
#include "servos.h"

#include <iostream>

namespace servos {

void resetDriver() {
}

void setAngle(int i, float angle) {
    ServoSim::instance().targetAngles.at(i) = angle;
}

} // namespace servos

void ServoSim::update() {
    auto &sim = ServoSim::instance();
    for (size_t i = 0; i < 12; ++i) {
        auto target = sim.targetAngles.at(i);
        auto &angle = sim.angles.at(i);

        angle -= (angle - target) / 3.;
    }
}

ServoSim &ServoSim::instance() {
    static auto servos = ServoSim{};
    return servos;
}
