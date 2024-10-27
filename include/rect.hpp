#ifndef RECT_HPP
#define RECT_HPP

#include <cstdint>

class Rect {
    public:
        Rect() {};
        Rect(int32_t left, int32_t top, int32_t width, int32_t height): left(left), top(top), width(width), height(height) {};
        Rect(int32_t width, int32_t height): width(width), height(height) {};
        Rect(const Rect& other): left(other.left), top(other.top), width(other.width), height(other.height) {};

        int32_t left = 0;
        int32_t top = 0;
        int32_t width = 0;
        int32_t height = 0;
};

#endif