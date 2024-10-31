#include <iostream>
#include <memory>
#include <cstdint>
#include <string>
#include <chrono>
#include <cmath>

#include <windows.h>
#include <glad/glad.h>

#include "game.hpp"
#include "window.hpp"
#include "graphics.hpp"
#include "rect.hpp"
#include "vector4.hpp"
#include "matrix4.hpp"
#include "uniform_buffer.hpp"
#include "settings.hpp"

struct UniformData {
    // float gameTime;
    Matrix4 world;
    Matrix4 translation;
    Matrix4 scale;
    Vector3 rotation;
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

    // rectangle
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

    m_uniformBuffers.push_back(m_graphics->create_uniform_buffer({
        "UniformData",
        sizeof(UniformData)
    }));

    m_shaderProgram -> set_uniform_buffer_slot("UniformData", 0);

    m_lastFrameTime = std::chrono::steady_clock::now();
    m_firstFrameTime = m_lastFrameTime;
}

void Game::on_destroy() {
}

void Game::on_update(float deltaTime) {
    render(deltaTime);
}

void Game::render(float deltaTime) {
    glClearColor(v4_unpack(m_background));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(m_polyVAO->get_id()); // set vertex array

    Rect rect = m_window->get_rect();
    float gameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(m_lastFrameTime - m_firstFrameTime).count() / 1000000000.0f;
    float x = sin(gameTime * 2);
    float y = cos(gameTime * 2);

    Matrix4 world, translation, scale;
    world.set_identity();
    // translation.set_translation(Vector3(x, y, 0.0f));
    // scale.set_scale(Vector3(1, 1, 1));

    Vector3 rotation;
    rotation.x = gameTime;
    rotation.y = gameTime;
    rotation.z = gameTime;

    UniformData data = {world, translation, scale, rotation};

    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_uniformBuffers[0]->get_id()); // set uniform buffer
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(UniformData), &data); // give data to uniform buffer

    glUseProgram(m_shaderProgram->get_id()); // set shader program
    glDrawArrays(GL_TRIANGLE_STRIP, 0, m_polyVAO->get_vertex_buffer_size()); // draw tris

    m_window->present(m_vsync);
}

void Game::quit() {
    m_running = false;
}