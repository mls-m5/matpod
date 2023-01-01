#include "control.h"
#include "idlecycle.h"
#include "led.h"
#include "server.h"
#include "servos.h"
#include "testprograms.h"
#include "udp.h"
#include "walkcycle.h"
#include "wifi.h"
#include <Arduino.h>
#include <cmath>

namespace {

enum class ServerType {
    Web,
    Udp,
};

ServerType serverType = ServerType::Udp;

} // namespace

void setup() {
    led::init();

    wifi::connect();

    Serial.println("trying to init servos");
    servos::resetDriver();
    servos::resetAngles();

    if (serverType == ServerType::Web) {
        server::init();
    }
    else {
        udp::init();
    }
}

namespace {

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

void demoControlsCycle(float step) {
    auto &control = Control::instance();
    static float phase = 0.;
    control.x = std::sin(phase / 5.);
    control.y = 1;
}

auto cycle = Cycle1{};
auto idleCycle = IdleCycle{};

} // namespace

void loop() {
    wifi::check();

    if (serverType == ServerType::Web) {
        server::handle();
    }
    else {
        // udp...
    }

    auto step = calculateStep();

    static int state = 1;

    bool enableIdleAnimation = false;

    auto &control = Control::instance();

    switch (state) {
    case 0:
        tests::program1();
        break;
    case 1: {
        auto demoControls = false;
        if (demoControls) {
            demoControlsCycle(step);
        }
        cycle.applyControls(control);
        cycle.update(step);

        if (enableIdleAnimation && !control.isActive()) {
            state = 2;
        }
        break;
    }
    case 2:
        idleCycle.update(step);
        if (control.isActive()) {
            state = 1;
        }

        break;
    }
}
