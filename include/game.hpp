#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <chrono>

#include "window.hpp"
#include "graphics.hpp"
#include "vertex_array.hpp"
#include "shader_program.hpp"
#include "vector4.hpp"

typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;

class Game {
    public:
        Game();
        ~Game();

        virtual void on_create();
        virtual void on_destroy();
        virtual void on_update(float deltaTime);
    
        void run();
        void platform_update();
        void quit();

    private:
        bool m_running = true;
        TimePoint m_lastFrameTime;

        Vector4 m_background = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
        
        VertexArrayObjectPtr m_trisVAO;
        ShaderProgramPtr m_shaderProgram;

        std::unique_ptr<GraphicsEngine> m_graphics = nullptr;
        std::unique_ptr<Window> m_window = nullptr;
};

#endif // GAME_HPP