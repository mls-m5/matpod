#include "servos.h"

void setup() {
    servos::resetDriver();
    for (size_t i = 0; i < 12; ++i) {
        servos::setAngle(i, 0);
    }
    servos::setAngle(1, .5);
}

void loop() {
}
