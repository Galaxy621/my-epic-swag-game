#include "window.hpp"
#include <assert.h>

#include <glad/glad.h>
#include <glad/glad_wgl.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_DESTROY: {
            auto window = (Window*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
            window->on_destroy();
            PostQuitMessage(0);
            break;
        }
        
        case WM_CLOSE: {
            PostQuitMessage(0);
            break;
        }

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

Rect Window::get_rect() {
    RECT rc;
    GetClientRect(m_handle, &rc);
    return Rect(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
}

Window::Window(LPCWSTR title, int32_t width, int32_t height) : title(title), width(width), height(height) {
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpszClassName = L"GameEngineWindow";
    wc.lpfnWndProc = &WndProc;
    wc.style = CS_OWNDC;

    auto classId = RegisterClassEx(&wc);
    assert(classId);

    RECT rc = {0, 0, width, height};
    AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

    m_handle = CreateWindowEx(
        0,
        MAKEINTATOM(classId),
        title,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, 
        CW_USEDEFAULT,
        rc.right - rc.left,
        rc.bottom - rc.top,
        NULL, NULL, NULL, NULL
    );

    assert(m_handle);
    SetWindowLongPtr(m_handle, GWLP_USERDATA, (LONG_PTR) this);

    ShowWindow(m_handle, SW_SHOW);
    UpdateWindow(m_handle);

    // OpenGL Render Context
    HDC hdc = GetDC(m_handle);

    int pixelFormatAttibutes[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        0
    };

    int32_t pixelFormat = 0;
    UINT numFormats = 0;

    wglChoosePixelFormatARB(hdc, pixelFormatAttibutes, nullptr, 1, &pixelFormat, &numFormats);
    assert(numFormats);

    PIXELFORMATDESCRIPTOR pfd = {};
    DescribePixelFormat(hdc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    SetPixelFormat(hdc, pixelFormat, &pfd);

    int32_t openGLAttributes[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 6,
        // WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    m_glContext = wglCreateContextAttribsARB(hdc, 0, openGLAttributes);
    assert(m_glContext);

}

Window::~Window() {
    wglDeleteContext(m_glContext);
    DestroyWindow(m_handle);
}

void Window::on_destroy() {
    m_handle = nullptr;
}

bool Window::is_closed() {
    return !m_handle;
}

void Window::make_current() {
    HDC hdc = GetDC(m_handle);
    wglMakeCurrent(hdc, m_glContext);
    ReleaseDC(m_handle, hdc);
}

void Window::present(bool vsync) {
    HDC hdc = GetDC(m_handle);
    wglSwapIntervalEXT(vsync);
    wglSwapLayerBuffers(hdc, WGL_SWAP_MAIN_PLANE);
    ReleaseDC(m_handle, hdc);
}
