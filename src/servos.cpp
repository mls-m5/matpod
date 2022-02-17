// Crodits for servo logic in this file goes to
// philisson: https://github.com/philsson

#include "servos.h"
#include <Adafruit_PWMServoDriver.h>
#include <cmath>

namespace {

auto driver = Adafruit_PWMServoDriver{};

int16_t angle2time(float angle) {
    constexpr float maxAngle = 1.43117; // observed by philip
    constexpr float minAngle = -maxAngle;
    constexpr float angleSpan = maxAngle - minAngle;

    // angle = std::clamp(angle, -maxAngle, maxAngle); // when c++17 comes
    angle = std::max(angle, minAngle);
    angle = std::min(angle, maxAngle);

    // constexpr auto servoMin = 190;
    // constexpr auto servoMax = 540;
    constexpr int16_t usMin = 600;
    constexpr int16_t usMax = 2400;
    constexpr int16_t usDiff = usMax - usMin;

    return usMin +
           static_cast<int16_t>(((angle - minAngle) / angleSpan) * usDiff);
}

} // namespace

namespace servos {

void resetDriver() {
    constexpr auto servoFreq = 60;

    driver.begin();
    driver.setPWMFreq(servoFreq);
}

void setAngle(int i, float angle) {
    driver.writeMicroseconds(i, angle2time(angle));
}

void resetAngles() {
    for (size_t i = 0; i < 12; ++i) {
        setAngle(i, 0);
    }
}

} // namespace servos
