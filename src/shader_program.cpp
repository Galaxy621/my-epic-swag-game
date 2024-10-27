#include "shader_program.hpp"
#include <glad/glad.h>

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(const ShaderProgramDesc& desc) {
    m_programId = glCreateProgram();
    if (!m_programId) throw std::runtime_error("Failed to create shader program");       

    attach(desc.vertexShaderSource, VERTEX_SHADER);
    attach(desc.fragmentShaderSource, FRAGMENT_SHADER);

    link();
}

ShaderProgram::~ShaderProgram() {
    for (uint32_t shaderId : m_attachedShaders) {
        glDetachShader(m_programId, shaderId);
        glDeleteShader(shaderId);
    }

    glDeleteProgram(m_programId);
}

void ShaderProgram::attach(const char* source, const ShaderType type) {
    std::string shader;
    std::ifstream shaderStream(source);
    if (!shaderStream.is_open()) throw std::runtime_error("Failed to open shader file");

    std::stringstream buffer;
    buffer << shaderStream.rdbuf();
    shader = buffer.str();
    shaderStream.close();

    uint32_t shaderId = glCreateShader(type == VERTEX_SHADER ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    if (!shaderId) throw std::runtime_error("Failed to create shader");

    const char* shaderSource = shader.c_str();
    glShaderSource(shaderId, 1, &shaderSource, nullptr);
    glCompileShader(shaderId);

	int result;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(shaderId, length, &length, message);
		std::cout << "Failed to compile " << (type == VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(shaderId);
	} else {
        // std::cout << "Successfully compiled " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        glAttachShader(m_programId, shaderId);
        m_attachedShaders[type] = shaderId;
    }


}

void ShaderProgram::link() {
    glLinkProgram(m_programId);
    glUseProgram(m_programId);
}