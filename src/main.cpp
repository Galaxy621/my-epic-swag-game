#define UNICODE
#define _UNICODE

#include <iostream>
#include <memory>
#include <stdexcept>

#include "game.hpp"

GameSettings settings = {
    "OpenGL Test", 1280, 720, true
};

int main() {

    try {
        auto game = std::make_unique<Game>(settings);
        game -> run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}