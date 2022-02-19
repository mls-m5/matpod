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

auto cycle = Cycle1{};

void loop() {
    server::handle();

    static auto phase = 0.f;

    switch (1) {
    case 0:
        tests::program1();
        break;
    case 1:
        auto demoControls = false;
        auto &control = Control::instance();
        if (demoControls) {
            control.x = std::sin(phase / 5.);
            control.y = 1;
        }
        cycle.applyControls(control);
        phase = cycle.update(phase);
    }
}
