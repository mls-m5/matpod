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

inline void moveLeg(int i, LegAngles angles, int indexOffset) {
    setAngle((i + indexOffset) % 6, angles.hip);
    setAngle((i + indexOffset) % 6 + 6, angles.knee);
}

/// Offset is if the hexapod should move in some other direction
inline void moveLeg(int i, int side, LegAngles angles, int indexOffset) {
    if (side == 0) {
        moveLeg(i, angles, indexOffset);
    }
    else {
        angles.flip();
        moveLeg(5 - i, angles, indexOffset);
    }
}

} // namespace servos
