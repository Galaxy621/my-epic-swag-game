#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "vector4.hpp"
#include "rect.hpp"
#include "vertex_array.hpp"
#include "shader_program.hpp"

class GraphicsEngine {
    public:
        GraphicsEngine();
        ~GraphicsEngine();

        VertexArrayObjectPtr create_vertex_array_object(const VertexBufferDesc& vertexData);
        ShaderProgramPtr create_shader_program(const ShaderProgramDesc& desc);
};

#endif // GRAPHICS_HPP