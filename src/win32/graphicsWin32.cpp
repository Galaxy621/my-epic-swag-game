#include <assert.h>
#include "graphics.hpp"

#include <glad/glad.h>
#include <glad/glad_wgl.h>

#include <stdexcept>

GraphicsEngine::GraphicsEngine() {
    WNDCLASSEX wc = {};
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = DefWindowProc;
    wc.lpszClassName = "OGLDummyWindow";
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.hInstance = GetModuleHandle(nullptr);

    ATOM classId = RegisterClassEx(&wc);
    assert(classId);

    HWND dummy = CreateWindowExA(
        0,
        "OGLDummyWindow",
        "OGLDummyWindow",
        0,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0, 0, wc.hInstance, 0
    );

    assert(dummy);

    HDC dummyDC = GetDC(dummy);

    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cAlphaBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;

    int pixelFormat = ChoosePixelFormat(dummyDC, &pfd);
    SetPixelFormat(dummyDC, pixelFormat, &pfd);

    HGLRC dummyCTX = wglCreateContext(dummyDC);
    assert(dummyCTX);

    bool res = wglMakeCurrent(dummyDC, dummyCTX);
    assert(res);

    if (!gladLoadWGL(dummyDC)) {
        throw std::runtime_error("Failed to load WGL extensions");
    }

    if (!gladLoadGL()) {
        throw std::runtime_error("Failed to load OpenGL extensions");
    }

    wglMakeCurrent(dummyDC, 0);
    wglDeleteContext(dummyCTX);
    ReleaseDC(dummy, dummyDC);
    DestroyWindow(dummy);
}

GraphicsEngine::~GraphicsEngine() {
}
