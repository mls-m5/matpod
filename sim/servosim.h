#pragma once

#include <array>

struct ServoSim {
    std::array<float, 12> angles;
    std::array<float, 12> targetAngles;

    void update();

    static ServoSim &instance();
};
