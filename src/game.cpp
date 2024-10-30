#include <iostream>
#include <memory>
#include <cstdint>
#include <string>

#include <windows.h>
#include <glad/glad.h>

#include "game.hpp"
#include "window.hpp"
#include "graphics.hpp"
#include "rect.hpp"
#include "vector4.hpp"
#include "uniform_buffer.hpp"
#include "settings.hpp"

struct UniformData {
    float gameTime;
    float windowWidth;
    float windowHeight;    
};

Game::Game(GameConfig& desc, const char* settingsPath) {
    // std::cout << glGetString(GL_VERSION) << std::endl;
    m_settings = std::make_shared<GameSettings>(settingsPath);

    int32_t width = m_settings->get_int("width");
    int32_t height = m_settings->get_int("height");
    m_vsync = m_settings->get_bool("vsync");

    m_graphics = std::make_unique<GraphicsEngine>();
    m_window = std::make_unique<Window>(desc.title, width, height);

    m_window->make_current();

    Rect rect = m_window->get_rect();
    glViewport(rect.left, rect.top, rect.width, rect.height);
}

Game::~Game() {
    auto lifetime = std::chrono::duration_cast<std::chrono::nanoseconds>(m_lastFrameTime - m_firstFrameTime);
    std::cout << "Game lifetime: " << lifetime.count() / 1000000.0f  << "ms" << std::endl;
    std::cout << "meow" << std::endl;
}

void Game::run() {

    on_create();

    while (m_running) {
        platform_update();    

        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(now - m_lastFrameTime);
        m_lastFrameTime = now;

        on_update(
            duration.count() / 1000000000.0f
        );
    }

    on_destroy();
}

void Game::on_create() {

    std::cout << "OpenGL version:   " << glGetString(GL_VERSION) << std::endl;
    std::cout << "OpenGL vendor:    " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Error:            " << glGetError() << std::endl;

    glEnable(GL_DEBUG_OUTPUT);

    const float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        1, 0, 0,

        -0.5f, 0.5f, 0.0f,
        0, 1, 0,

        0.5f, -0.5f, 0.0f,
        0, 0, 1,

        0.5f, 0.5f, 0.0f,
        1, 1, 0,
    };

    VertexAttribute attributes[] = {
        {3},
        {3}
    };

    m_polyVAO = m_graphics->create_vertex_array_object({
        (void*) vertices,
        6 * sizeof(float),
        4,

        attributes,
        2
    });

    m_shaderProgram = m_graphics->create_shader_program({
        "assets/shaders/tris.vert",
        "assets/shaders/tris.frag"
    });

    auto buff = register_uniform_buffer({
        "UniformData",
        sizeof(UniformData)
    });

    m_lastFrameTime = std::chrono::steady_clock::now();
    m_firstFrameTime = m_lastFrameTime;
}

UniformBufferPtr Game::register_uniform_buffer(const UniformBufferDesc& data) {
    auto buff = m_graphics->create_uniform_buffer(data);
    m_uniformBuffers.push_back(buff);
    m_shaderProgram->set_uniform_buffer_slot(data.identifier.c_str(), m_uniformBuffers.size() - 1);
    return buff;
}

void Game::on_destroy() {
}

void Game::on_update(float deltaTime) {
    render(deltaTime);
}

void Game::render(float deltaTime) {
    glClearColor(v4_unpack(m_background));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Rect rect = m_window->get_rect();;
    float width = (float) rect.width;
    float height = (float) rect.height;

    UniformData data = {
        std::chrono::duration_cast<std::chrono::nanoseconds>(m_lastFrameTime - m_firstFrameTime).count() / 1000000000.0f,
        width,
        height
    };

    glBindVertexArray(m_polyVAO->get_id()); // set vertex array

    for (int i = 0; i < m_uniformBuffers.size(); i++) {
        glBindBufferBase(GL_UNIFORM_BUFFER, i, m_uniformBuffers[i]->get_id()); // set uniform buffer
        glBufferSubData(GL_UNIFORM_BUFFER, i, sizeof(UniformData), &data); // give data to uniform buffer
    }

    // glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_uniformBuffer->get_id()); // set uniform buffer
    // glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(UniformData), &data); // give data to uniform buffer

    glUseProgram(m_shaderProgram->get_id()); // set shader program
    glDrawArrays(GL_TRIANGLE_STRIP, 0, m_polyVAO->get_vertex_buffer_size()); // draw tris

    m_window->present(m_vsync);
}

void Game::quit() {
    m_running = false;
}