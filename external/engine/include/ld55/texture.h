#pragma once

#include <string>
#include <cstdint>

namespace ld55 {
    class Texture {
    public:
        Texture(const void* data);
        Texture(const void* data, int32_t wrapMode, int32_t magFilter, int32_t minFilter, bool mipmap);

        uint32_t getId() { return id; };
        void bind();

    private:
        uint32_t id;
        static uint32_t loadTexture(const void* data,
                             int32_t wrapMode, int32_t magFilter,
                             int32_t minFilter, bool mipmap);
    };
}