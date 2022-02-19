#include "led.h"
#include <Arduino.h>

namespace {

constexpr int LED_BUILTIN = 2;

}

namespace led {

void init() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void flash() {
    for (int i = 0; i < 5; ++i) {
        usleep(100000);
        digitalWrite(LED_BUILTIN, HIGH);
        usleep(100000);
        digitalWrite(LED_BUILTIN, LOW);
    }
}

} // namespace led
