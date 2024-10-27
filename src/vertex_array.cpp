#include "vertex_array.hpp"

#include <glad/glad.h>
#include <stdexcept>
#include <iostream>

VertexArrayObject::VertexArrayObject(const VertexBufferData& vertexData) {
    glGenBuffers(1, &m_vertexBufferId);
    if (!m_vertexBufferId) throw std::runtime_error("Failed to create vertex array object");

    glGenVertexArrays(1, &m_vertexArrayObjectId);
    if (!m_vertexArrayObjectId) throw std::runtime_error("Failed to create vertex array object");
    glBindVertexArray(m_vertexArrayObjectId);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, vertexData.vertexSize * vertexData.listSize, vertexData.verticesList, GL_STATIC_DRAW);

    int vertexSize = vertexData.vertexSize / sizeof(float);
    glVertexAttribPointer(0, vertexSize, GL_FLOAT, GL_FALSE, vertexData.vertexSize, 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    m_vertexBufferData = vertexData;
}

VertexArrayObject::~VertexArrayObject() {
    glDeleteBuffers(1, &m_vertexBufferId);
    glDeleteVertexArrays(1, &m_vertexArrayObjectId);
}

uint32_t VertexArrayObject::get_id() {
    return m_vertexArrayObjectId;
}

uint32_t VertexArrayObject::get_vertex_buffer_size() {
    return m_vertexBufferData.listSize;
}

uint32_t VertexArrayObject::get_vertex_size() {
    return m_vertexBufferData.vertexSize;
}