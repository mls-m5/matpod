#pragma once

#include "legangles.h"
#include <memory>

namespace servos {

void resetDriver();
void setAngle(int i, float angle);

inline void resetAngles() {
    for (size_t i = 0; i < 12; ++i) {
        setAngle(i, 0);
    }
}

inline void moveLeg(int i, LegAngles angles) {
    setAngle(i, angles.hip);
    setAngle(i + 6, angles.knee);
}

} // namespace servos
