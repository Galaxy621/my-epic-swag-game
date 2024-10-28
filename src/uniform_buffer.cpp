#include "uniform_buffer.hpp"

#include <glad/glad.h>
#include <stdexcept>

UniformBuffer::UniformBuffer(const UniformBufferDesc& desc) : m_size(desc.size) {
    glGenBuffers(1, &m_id);
    if (!m_id) throw std::runtime_error("Failed to create uniform buffer");

    glBindBuffer(GL_UNIFORM_BUFFER, m_id);
    glBufferData(GL_UNIFORM_BUFFER, m_size, nullptr, GL_STATIC_DRAW);

    // Unbind
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UniformBuffer::~UniformBuffer() {
    glDeleteBuffers(1, &m_id);
}

uint32_t UniformBuffer::get_id() {
    return m_id;
}