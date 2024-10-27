#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <Windows.h>
#include <rect.hpp>
#include <cstdint>

class Window {
    public:
        Window(LPCWSTR title, int32_t width, int32_t height);
        ~Window();

        void on_destroy();
        bool is_closed();
        Rect get_rect();

        void make_current();
        void present(bool vsync);

    private:
        HWND m_handle = nullptr;
        HGLRC m_glContext = nullptr;

        LPCWSTR title;
        int32_t width;
        int32_t height;
};

#endif