#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <chrono>

#include "window.hpp"
#include "graphics.hpp"
#include "vertex_array.hpp"
#include "shader_program.hpp"
#include "vector4.hpp"
#include "uniform_buffer.hpp"

typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;

struct GameSettings {
    const char* title;
    int32_t width;
    int32_t height;
    bool vsync;
};

class Game {
    public:
        Game(GameSettings& desc);
        ~Game();

        virtual void on_create();
        virtual void on_destroy();
        virtual void on_update(float deltaTime);
    
        void render(float deltaTime);

        void run();
        void platform_update();
        void quit();

    private:
        bool m_running = true;
        bool m_vsync = true;

        TimePoint m_lastFrameTime;
        TimePoint m_firstFrameTime;

        Vector4 m_background = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
        
        VertexArrayObjectPtr m_polyVAO;
        ShaderProgramPtr m_shaderProgram;
        UniformBufferPtr m_uniformBuffer;

        std::unique_ptr<GraphicsEngine> m_graphics = nullptr;
        std::unique_ptr<Window> m_window = nullptr;
};

#endif // GAME_HPP