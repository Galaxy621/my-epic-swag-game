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