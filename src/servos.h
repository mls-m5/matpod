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

inline void moveLeg(int i, int side, LegAngles angles) {
    if (side == 0) {
        moveLeg(i, angles);
    }
    else {
        angles.flip();
        moveLeg(5 - i, angles);
    }
}

} // namespace servos
