#pragma once

struct Control {
    float turn = 0;
    float x = 0;
    float y = 0;

    // If controls is other than zero
    bool isActive();

    static Control &instance();
};
