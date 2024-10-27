#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include "window.hpp"
#include "graphics.hpp"
#include "vertex_array.hpp"
#include "shader_program.hpp"

class Game {
    public:
        Game();
        ~Game();

        virtual void on_create();
        virtual void on_destroy();
        virtual void on_update();

        void run();
        void quit();

    private:
        bool m_running = true;
        
        VertexArrayObjectPtr m_trisVAO;
        ShaderProgramPtr m_shaderProgram;

        std::unique_ptr<GraphicsEngine> m_graphics = nullptr;
        std::unique_ptr<Window> m_window = nullptr;
};

#endif // GAME_HPP