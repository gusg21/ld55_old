#pragma once

#include <string>
#include <cstdint>

namespace ld55 {
    class Texture {
    public:
        Texture(const void* data, uint32_t width, uint32_t height);
        Texture(const void* data, uint32_t width, uint32_t height, int32_t wrapMode, int32_t magFilter, int32_t minFilter, bool mipmap);

        uint32_t getId() { return id; };
        void bindToTextureUnit(uint32_t unit);

    private:
        uint32_t id;
        static uint32_t loadTexture(const void* data, uint32_t width, uint32_t height,
                             int32_t wrapMode, int32_t magFilter,
                             int32_t minFilter, bool mipmap);
    };
}