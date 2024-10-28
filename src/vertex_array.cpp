#include "vertex_array.hpp"

#include <glad/glad.h>
#include <assert.h>
#include <stdexcept>
#include <iostream>

VertexArrayObject::VertexArrayObject(const VertexBufferDesc& vertexData) {

    assert(vertexData.listSize);
    assert(vertexData.vertexSize);
    assert(vertexData.verticesList);

    glGenVertexArrays(1, &m_vertexArrayObjectId);
    if (!m_vertexArrayObjectId) throw std::runtime_error("Failed to create vertex array object");
    glBindVertexArray(m_vertexArrayObjectId);

    glGenBuffers(1, &m_vertexBufferId);
    if (!m_vertexBufferId) throw std::runtime_error("Failed to create vertex array object");
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, vertexData.vertexSize * vertexData.listSize, vertexData.verticesList, GL_STATIC_DRAW);

    for (uint32_t i = 0; i < vertexData.attributeCount; i++) {
        VertexAttribute attribute = vertexData.attributes[i];

        glVertexAttribPointer(
            i,
            attribute.elementCount,
            GL_FLOAT,
            GL_FALSE,
            vertexData.vertexSize,
            // (void*) (i * sizeof(float))
            (void*) ((i == 0) ? 0 : (vertexData.attributes[i - 1].elementCount * sizeof(float)))
        );

        glEnableVertexAttribArray(i);
    }

    // int vertexSize = vertexData.vertexSize / sizeof(float);
    // glVertexAttribPointer(0, vertexSize, GL_FLOAT, GL_FALSE, vertexData.vertexSize, 0);
    // glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    m_VertexBufferDesc = vertexData;
}

VertexArrayObject::~VertexArrayObject() {
    glDeleteBuffers(1, &m_vertexBufferId);
    glDeleteVertexArrays(1, &m_vertexArrayObjectId);
}

uint32_t VertexArrayObject::get_id() {
    return m_vertexArrayObjectId;
}

uint32_t VertexArrayObject::get_vertex_buffer_size() {
    return m_VertexBufferDesc.listSize;
}

uint32_t VertexArrayObject::get_vertex_size() {
    return m_VertexBufferDesc.vertexSize;
}