#define UNICODE
#define _UNICODE

#include <iostream>
#include <memory>
#include <stdexcept>

#include "game.hpp"
#include "settings.hpp"

int main() {
    try {
        GameConfig config = {"OpenGL Test"};
        auto game = std::make_unique<Game>(config, "settings.ini");
        game -> run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}