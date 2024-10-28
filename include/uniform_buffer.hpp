#ifndef UNIFORM_BUFFER_HPP
#define UNIFORM_BUFFER_HPP

#include <cstdint>
#include <memory>

struct UniformBufferDesc {
    uint32_t size;
};

class UniformBuffer {
    public:
        UniformBuffer(const UniformBufferDesc& desc);
        ~UniformBuffer();

        uint32_t get_id();

    private:
        uint32_t m_size;
        uint32_t m_id;
};

typedef std::shared_ptr<UniformBuffer> UniformBufferPtr;

#endif // UNIFORM_BUFFER_HPP