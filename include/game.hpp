#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <chrono>
#include <vector>

#include "window.hpp"
#include "graphics.hpp"
#include "vertex_array.hpp"
#include "shader_program.hpp"
#include "vector4.hpp"
#include "uniform_buffer.hpp"
#include "settings.hpp"

typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;

struct GameConfig {
    const char* title;
};

class Game {
    public:
        Game(GameConfig& desc, const char* settingsPath);
        ~Game();

        virtual void on_create();
        virtual void on_destroy();
        virtual void on_update(float deltaTime);
    
        void render(float deltaTime);
        UniformBufferPtr register_uniform_buffer(const UniformBufferDesc& data);

        void run();
        void platform_update();
        void quit();

    private:
        bool m_running = true;
        bool m_vsync = true;

        TimePoint m_lastFrameTime;
        TimePoint m_firstFrameTime;

        Vector4 m_background = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
        
        GameSettingsPtr m_settings;
        VertexArrayObjectPtr m_polyVAO;
        ShaderProgramPtr m_shaderProgram;
        std::vector<UniformBufferPtr> m_uniformBuffers;
        // UniformBufferPtr m_uniformBuffer;

        std::unique_ptr<GraphicsEngine> m_graphics = nullptr;
        std::unique_ptr<Window> m_window = nullptr;
};

#endif // GAME_HPP