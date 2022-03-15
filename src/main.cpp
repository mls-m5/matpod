#include "control.h"
#include "led.h"
#include "server.h"
#include "servos.h"
#include "testprograms.h"
#include "walkcycle.h"
#include "wifi.h"
#include <Arduino.h>

#include <cmath>

void setup() {
    led::init();

    wifi::connect();

    servos::resetDriver();
    servos::resetAngles();
    server::init();
}

namespace {

auto cycle = Cycle1{};

unsigned long lastTime = 0;

float calculateStep() {
    if (lastTime == 0) {
        lastTime = millis();
    }

    auto now = millis();
    auto diff = now - lastTime;

    lastTime = now;

    return diff / 1000.f;
}

} // namespace

void loop() {
    server::handle();

    auto step = calculateStep();

    switch (1) {
    case 0:
        tests::program1();
        break;
    case 1: {
        auto demoControls = false;
        auto &control = Control::instance();
        static float phase = 0.;
        if (demoControls) {
            control.x = std::sin(phase / 5.);
            control.y = 1;
        }
        cycle.applyControls(control);
        cycle.update(step);
        break;
    }
    case 2:

        break;
    }
}
