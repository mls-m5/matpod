#pragma once

struct Control {
    float x = 0;
    float y = 1;

    static Control &instance();
};
