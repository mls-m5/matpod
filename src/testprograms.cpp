#include "testprograms.h"
#include "servos.h"

namespace tests {

void program1() {

    static auto dir = -.4f;
    static auto leg = 0;
    if (++leg >= 12) {
        leg = 0;
    }

    if (leg == 0) {
        dir *= -1.f;
    }

    servos::setAngle(leg, dir);

    usleep(500000);
}

} // namespace tests
