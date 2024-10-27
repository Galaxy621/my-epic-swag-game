#define UNICODE
#define _UNICODE

#include <iostream>
#include "game.hpp"

int main() {

    try {
        Game game;
        game.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}