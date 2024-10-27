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

        VertexArrayObjectPtr create_vertex_array_object(const VertexBufferData& vertexData);
        ShaderProgramPtr create_shader_program(const ShaderProgramDesc& desc);
        
        void set_vertex_array_object(const VertexArrayObjectPtr& vertexData);
        void set_shader_program(const ShaderProgramPtr& shaderProgram);

        void set_viewport(const Rect& rect);
        void draw_tris(uint32_t count, uint32_t offset);
        void clear(const Vector4& color);
};

#endif // GRAPHICS_HPP