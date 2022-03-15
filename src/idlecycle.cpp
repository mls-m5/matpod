#include "idlecycle.h"
#include "servos.h"
#include "sharedvalues.h"
#include <cmath>

void IdleCycle::update(float step) {
    auto &values = sharedValues();
    for (int i = 0; i < 6; ++i) {
        servos::moveLeg(
            i,
            {static_cast<float>(std::sin(phase)) * .2f, values.legBottomAngle});
    }
    phase += step;
}
