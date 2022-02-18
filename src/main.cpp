#include "control.h"
#include "servos.h"
#include "testprograms.h"
#include "walkcycle.h"

#include <cmath>

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
        auto demoControls = false;
        if (demoControls) {
            cycle.walkAmount(1);
            cycle.turnAmount(std::sin(phase / 5.));
        }
        else {
            auto &control = Control::instance();
            cycle.turnAmount(control.x);
            cycle.walkAmount(control.y);
        }
        phase = cycle.update(phase);
    }
}
