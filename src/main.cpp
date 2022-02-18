#include "servos.h"
#include "testprograms.h"
#include "walkcycle.h"

void setup() {
    servos::resetDriver();
    servos::resetAngles();
}

void loop() {
    static auto phase = 0.f;

    switch (1) {
    case 0:
        tests::program1();
        break;
    case 1:
        phase = walkCycle(phase);
    }
}
