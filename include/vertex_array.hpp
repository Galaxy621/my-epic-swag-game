#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <cstdint>
#include <memory>

struct VertexAttribute {
    uint32_t elementCount;
};

struct VertexBufferDesc {
    void* verticesList = nullptr;
    uint32_t vertexSize = 0;
    uint32_t listSize = 0;

    VertexAttribute* attributes = nullptr;
    uint32_t attributeCount = 0;
};

class VertexArrayObject {
    public:
        VertexArrayObject(const VertexBufferDesc& vertexData);
        ~VertexArrayObject();

        uint32_t get_id();
        uint32_t get_vertex_buffer_size();
        uint32_t get_vertex_size();

    private:
        uint32_t m_vertexBufferId = 0;
        uint32_t m_vertexArrayObjectId = 0;
        VertexBufferDesc m_VertexBufferDesc;
};

typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;

#endif