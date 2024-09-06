#pragma once

// Made up basic protocol for sending axis and buttons
#include <cstdint>
#include <limits>

struct Payload {
    uint8_t numAxis = 4; // Used for the protocol
    int16_t x1 = 0;
    int16_t y1 = 0;
    int16_t x2 = 0;
    int16_t y2 = 0;
    uint8_t numButtons = 12; // Used for the protocol
    uint16_t buttons = 0;

    bool button(int num) {
        return buttons & (1 << num);
    }

    void button(int num, bool value) {
        if (value) {
            buttons |= (1 << num);
        }
        else {
            buttons &= ~(1 << num);
        }
    }

    int16_t axis(int num) {
        return (&x1)[num];
    }

    // Axis as float
    float faxis(int num) {
        return static_cast<float>(axis(num)) /
               static_cast<float>(std::numeric_limits<int16_t>::max());
    }
};
