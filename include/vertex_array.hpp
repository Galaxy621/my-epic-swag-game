#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <cstdint>
#include <memory>

struct VertexBufferData {
    void* verticesList = nullptr;
    uint32_t vertexSize = 0;
    uint32_t listSize = 0;
};

class VertexArrayObject {
    public:
        VertexArrayObject(const VertexBufferData& vertexData);
        ~VertexArrayObject();

        uint32_t get_id();
        uint32_t get_vertex_buffer_size();
        uint32_t get_vertex_size();

    private:
        uint32_t m_vertexBufferId = 0;
        uint32_t m_vertexArrayObjectId = 0;
        VertexBufferData m_vertexBufferData;
};

typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;

#endif