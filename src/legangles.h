#pragma once

struct LegAngles {
    LegAngles(float hip, float knee) : hip{hip}, knee{knee} {
    }

    float hip = 0;
    float knee = 0;

    void flip() {
        hip = -hip;
    }

    LegAngles &offset(float angle) {
        hip += angle;
        return *this;
    }
};
