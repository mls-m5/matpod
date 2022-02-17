#pragma once

#include <memory>

namespace servos {

void resetDriver();
void resetAngles();
void setAngle(int i, float angle);

} // namespace servos
