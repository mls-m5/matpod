#pragma once

struct Control {
    float x = 0;
    float y = 0;

    static Control &instance();
};
