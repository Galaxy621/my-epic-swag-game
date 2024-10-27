#include <iostream>

#include "game.hpp"
#include "window.hpp"
#include "graphics.hpp"

void Game::run() {

    on_create();

    while (m_running) {
        MSG msg = {};

        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                quit();
                continue;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        on_update();
    }

    on_destroy();
}