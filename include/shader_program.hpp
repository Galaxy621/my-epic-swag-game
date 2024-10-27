#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <cstdint>
#include <memory>

enum ShaderType {
    VERTEX_SHADER = 0,
    FRAGMENT_SHADER = 1
};

struct ShaderProgramDesc {
    const char* vertexShaderSource;
    const char* fragmentShaderSource;
};

class ShaderProgram {
    public:
        ShaderProgram(const ShaderProgramDesc& desc);
        ~ShaderProgram();

        uint32_t get_id() const { return m_programId; }

    private:
        void attach(const char* source, const ShaderType type);
        void link();

        uint32_t m_programId = 0;
        uint32_t m_attachedShaders[2] = {0, 0};
};

typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;

#endif // SHADER_PROGRAM_HPP