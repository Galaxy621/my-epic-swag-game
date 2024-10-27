#include <iostream>
#include <memory>

#include <glad/glad.h>

#include "game.hpp"
#include "window.hpp"
#include "graphics.hpp"
#include "rect.hpp"

Game::Game() {
    // std::cout << glGetString(GL_VERSION) << std::endl;

    m_graphics = std::make_unique<GraphicsEngine>();
    m_window = std::make_unique<Window>("Game", 1280, 720);

    m_window->make_current();
    m_graphics->set_viewport(m_window->get_rect());
}

Game::~Game() {
    std::cout << "meow" << std::endl;
}

void Game::on_create() {

    std::cout << "OpenGL version:   " << glGetString(GL_VERSION) << std::endl;
    std::cout << "OpenGL vendor:    " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Error:            " << glGetError() << std::endl;

    glEnable(GL_DEBUG_OUTPUT);

    const float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    m_trisVAO = m_graphics->create_vertex_array_object({
        (void*) vertices,
        3 * sizeof(float),
        3
    });

    m_shaderProgram = m_graphics->create_shader_program({
        "assets/shaders/tris.vert",
        "assets/shaders/tris.frag"
    });
}

void Game::on_destroy() {
}

void Game::on_update() {
    m_graphics->clear(Vector4(1.0f, 0.0f, 0.0f, 1.0f));

    m_graphics->set_vertex_array_object(m_trisVAO);
    m_graphics->set_shader_program(m_shaderProgram);
    m_graphics->draw_tris(m_trisVAO->get_vertex_buffer_size(), 0);

    m_window->present(false);
}

void Game::quit() {
    m_running = false;
}