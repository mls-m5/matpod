#include "walkcycle.h"
#include "servos.h"
#include "utils.h"
#include <Arduino.h>
#include <cmath>

namespace {

float cycle(float phase) {
    return phase - std::floor(phase);
}

float zeroMiddle(float value) {
    return value - .5f;
}

unsigned long lastTime = 0;

} // namespace

LegAngles Cycle1::legCycle(float phase) {
    phase = cycle(phase);

    constexpr float legBottomAngle = -1.f;
    constexpr float stepHeight = .8f;

    if (phase < _ratio) {
        return LegAngles{zeroMiddle(phase / _ratio) * _stepLen, legBottomAngle};
    }
    else {
        auto invRatio = 1. - _ratio;
        return LegAngles{zeroMiddle((1.f - (phase - _ratio) / invRatio)) *
                             _stepLen,
                         legBottomAngle + stepHeight * _stepHeightAmount};
    }
}

float Cycle1::legOffset(int index) {
    if (index == 0) {
        return -_offset;
    }
    else if (index == 2) {
        return _offset;
    }

    return 0;
}

float Cycle1::legDirectionScale(int index, int side) {
    auto ret = 0.f;

    ret += _walkAmount;

    if (side) {
        ret += _turnAmount;
    }
    else {
        ret -= _turnAmount;
    }

    auto invScale = std::abs(_walkAmount) + std::abs(_turnAmount);
    invScale = std::max(1.f, invScale);

    return ret / invScale;
}

Cycle1::Cycle1() {
    offsetPattern(0);
}

float Cycle1::update(float phase) {
    if (lastTime == 0) {
        lastTime = millis();
    }

    auto now = millis();
    auto diff = now - lastTime;

    auto step = diff / 10.f * .01f * _speed;

    phase += step;

    for (size_t i = 0; i < 6; ++i) {
        auto leg = legCycle(phase + _phaseOffset.at(i));
        auto index = i % 3;
        auto side = i >= 3;
        leg.hip *= legDirectionScale(index, side);
        servos::moveLeg(index, side, leg.offset(legOffset(index)));
    }

    lastTime = now;

    return phase;
}

void Cycle1::offsetPattern(int index) {
    for (auto &o : _phaseOffset) {
        o = 0;
    }

    if (index == 0) {
        _phaseOffset.at(0) = .5;
        _phaseOffset.at(2) = .5;
        _phaseOffset.at(4) = .5;
    }
    else if (index == 1) {
        // _phaseOffset.at(0) = _phaseOffset.at(5) = 0;
        _phaseOffset.at(1) = _phaseOffset.at(4) = 1.f / 3.f;
        _phaseOffset.at(2) = _phaseOffset.at(3) = 2.f / 3.f;
    }
    else if (index == 2) {
        for (size_t i = 0; i < 3; ++i) {
            _phaseOffset.at(i) = static_cast<float>(i) / 6.f;
            _phaseOffset.at(i + 3) = static_cast<float>(i) / 6.f + 2.f / 3.f;
        }
    }
}

void Cycle1::applyControls(Control control) {
    float prescale = 3;
    control.x = clamp(control.x, -1.f, 1.f);
    control.y = clamp(control.y, -1.f, 1.f);

    auto x = control.x * prescale;
    auto y = control.y * prescale;

    auto len = std::abs(x) + std::abs(y);

    auto downScale = 1.f;

    _stepHeightAmount = 1;

    if (len < .1) {
        _speed = 0;
        _stepHeightAmount = 0;
    }
    else if (len > 1.f) {
        downScale = 1. / len;
        _speed = std::max(std::abs(x), std::abs(y));
    }
    else {
        _speed = 1;
    }

    _turnAmount = x * downScale;
    _walkAmount = y * downScale;
}
