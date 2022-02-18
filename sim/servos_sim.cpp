#include "servos.h"

#include <iostream>

namespace servos {

void resetDriver() {
}

void setAngle(int i, float angle) {
    std::cout << "setting angle " << i << " to " << angle << std::endl;
}

void resetAngles() {
    for (size_t i = 0; i < 12; ++i) {
        setAngle(i, 0);
    }
}

} // namespace servos
