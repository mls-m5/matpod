#include "servos.h"
#include "testprograms.h"
#include "walkcycle.h"

void setup() {
    servos::resetDriver();
    servos::resetAngles();
}

auto cycle = Cycle1{};

void loop() {
    static auto phase = 0.f;

    switch (1) {
    case 0:
        tests::program1();
        break;
    case 1:
        phase = cycle.update(phase);
    }
}
