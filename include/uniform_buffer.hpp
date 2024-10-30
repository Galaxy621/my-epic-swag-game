#ifndef UNIFORM_BUFFER_HPP
#define UNIFORM_BUFFER_HPP

#include <cstdint>
#include <memory>
#include <string>

struct UniformBufferDesc {
    std::string identifier;
    uint32_t size;
};

class UniformBuffer {
    public:
        UniformBuffer(const UniformBufferDesc& desc);
        ~UniformBuffer();

        uint32_t get_id();
        std::string get_identifier();

    private:
        std::string m_identifier;
        uint32_t m_size;
        uint32_t m_id;
};

typedef std::shared_ptr<UniformBuffer> UniformBufferPtr;

#endif // UNIFORM_BUFFER_HPP