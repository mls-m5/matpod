#include "servos.h"
#include "testprograms.h"

void setup() {
    servos::resetDriver();
    servos::resetAngles();
}

void loop() {
    tests::program1();
}
