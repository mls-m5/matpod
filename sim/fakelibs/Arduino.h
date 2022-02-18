/// Header to fake arduino

#pragma once

#include <thread>

inline void usleep(int useconds) {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1us * useconds);
}
