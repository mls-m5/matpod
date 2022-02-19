#pragma once

#include <Arduino.h>
#include <cctype>

#ifndef ARDUINO
#include <string>
#endif

// Because platformio does not have c++17 yet
struct StrView {

    static constexpr size_t npos = -1;

    static size_t length(const char *c) {
        size_t len = 0;
        for (; c[len]; ++len) {
        }
        return len;
    }

    StrView(const char *d) : data{d}, len{length(d)} {
    }

    StrView(const char *d, size_t len) : data{d}, len{len} {
    }

    StrView() = default;
    StrView(StrView &) = default;
    StrView(StrView &&) = default;
    StrView &operator=(StrView &) = default;
    StrView &operator=(StrView &&) = default;

    inline size_t find(char c, size_t start = 0) {
        for (size_t i = start; i < len; ++i) {
            if (data[i] == c) {
                return i;
            }
        }
        return npos;
    }

    // This does not seem to work on arduino
    StrView substr(size_t pos, size_t size) const {
        return StrView{data + pos, size};
    }

    char front() const {
        return *data;
    }

    char back() const {
        return *(data + len - 1);
    }

    bool empty() const {
        return len == 0;
    }

    const char *data = nullptr;
    size_t len = 0;

    float toFloat() {

#ifdef ARDUINO
        return atof(data);
#else
        return std::stof(std::string{data, len});
#endif
    }
};
