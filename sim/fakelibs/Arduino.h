/// Header to fake arduino

#pragma once

#include <chrono>
#include <thread>

inline void usleep(int useconds) {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1us * useconds);
}

inline unsigned long millis() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::high_resolution_clock::now().time_since_epoch())
        .count();
}
