#pragma once

#include "control.h"
#include "legangles.h"
#include <array>

struct Cycle1 {
    Cycle1();
    float update(float phase);

    void offsetPattern(int index);

    void applyControls(Control control);

private:
    LegAngles legCycle(float phase);
    float legOffset(int index);
    float phaseOffset(int index, int side);

    float legDirectionScale(int index, int side);

    float _ratio = .8;
    float _offset = .4; // How much back and front feet will be angled outwards
    float _stepLen = .6;

    std::array<float, 6> _phaseOffset;

    float _walkAmount = 1;
    float _turnAmount = 0;
    float _speed = 1;
    float _stepHeightAmount = 1;
};
