#include "control.h"

Control &Control::instance() {
    static auto control = Control{};
    return control;
}
