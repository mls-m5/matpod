#pragma once

struct LegAngles {
    float hip = 0;
    float knee = 0;

    void flip() {
        hip = -hip;
    }
};
