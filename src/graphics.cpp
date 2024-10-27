#include <assert.h>
#include <stdexcept>
#include <iostream>

#include "graphics.hpp"

#include <glad/glad.h>
#include <glad/glad_wgl.h>

VertexArrayObjectPtr GraphicsEngine::create_vertex_array_object(const VertexBufferData& vertexData) {
    return std::make_shared<VertexArrayObject>(vertexData);
}

ShaderProgramPtr GraphicsEngine::create_shader_program(const ShaderProgramDesc& desc) {
    return std::make_shared<ShaderProgram>(desc);
}

void GraphicsEngine::set_vertex_array_object(const VertexArrayObjectPtr& vao) {
    glBindVertexArray(vao->get_id());
}

void GraphicsEngine::set_shader_program(const ShaderProgramPtr& shaderProgram) {
    glUseProgram(shaderProgram->get_id());
}

void GraphicsEngine::set_viewport(const Rect& rect) {
    glViewport(rect.left, rect.top, rect.width, rect.height);
}

void GraphicsEngine::clear(const Vector4& color) {
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsEngine::draw_tris(uint32_t count, uint32_t offset) {
    glDrawArrays(GL_TRIANGLES, offset, count);
}