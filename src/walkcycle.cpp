#include "walkcycle.h"
#include "servos.h"
#include <Arduino.h>
#include <cmath>

namespace {

float cycle(float phase) {
    return phase - std::floor(phase);
}

float zeroMiddle(float value) {
    return value - .5f;
}

} // namespace

LegAngles Cycle1::legCycle(float phase) {
    phase = cycle(phase);

    if (phase < _ratio) {
        return LegAngles{zeroMiddle(phase / _ratio) * _stepLen, -1.f};
    }
    else {
        auto invRatio = 1. - _ratio;
        return LegAngles{
            zeroMiddle((1.f - (phase - _ratio) / invRatio)) * _stepLen, -.2f};
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

Cycle1::Cycle1() {
    setOffsetPattern(0);
}

float Cycle1::update(float phase) {
    auto step = .01f;

    for (size_t i = 0; i < 6; ++i) {
        auto leg = legCycle(phase + _phaseOffset.at(i));
        servos::moveLeg(i % 3, i >= 3, leg.offset(legOffset(i % 3)));
    }

    usleep(1000 * step);

    return phase + step;
}

void Cycle1::setOffsetPattern(int index) {
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
