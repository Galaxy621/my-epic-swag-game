#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <Windows.h>
#include <rect.hpp>

class Window {
    public:
        Window(LPCWSTR title, int width, int height);
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
        int width;
        int height;
};

#endif