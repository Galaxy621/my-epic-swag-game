#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <cstdint>

#include "vector4.hpp"
#include "rect.hpp"
#include "vertex_array.hpp"
#include "shader_program.hpp"
#include "uniform_buffer.hpp"

enum TriangleType {
    TRIANGLE_LIST = 0,
    TRIANGLE_STRIP = 1
};

class GraphicsEngine {
    public:
        GraphicsEngine();
        ~GraphicsEngine();

        VertexArrayObjectPtr create_vertex_array_object(const VertexBufferDesc& vertexData);
        ShaderProgramPtr create_shader_program(const ShaderProgramDesc& desc);
        UniformBufferPtr create_uniform_buffer(const UniformBufferDesc& desc);
};

#endif // GRAPHICS_HPP