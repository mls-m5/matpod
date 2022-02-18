#pragma once

#include <cmath>

template <typename T>
inline auto clamp(T value, T min, T max) {
    value = std::max(value, min);
    value = std::min(value, max);
    return value;
}
