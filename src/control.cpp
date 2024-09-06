#include "control.h"
#include <cmath>

bool Control::isActive() {
    return std::abs(turn) > .1 || std::abs(y) > .1;
}

Control &Control::instance() {
    static auto control = Control{};
    return control;
}
