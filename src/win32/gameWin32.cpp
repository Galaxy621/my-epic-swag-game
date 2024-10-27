#include <iostream>

#include "game.hpp"
#include "window.hpp"
#include "graphics.hpp"

void Game::platform_update() {
    MSG msg = {};

    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            quit();
            continue;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}