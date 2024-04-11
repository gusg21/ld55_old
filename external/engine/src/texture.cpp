//
// Created by angus.goucher on 4/5/2024.
//

#include "ld55/texture.h"

#include <string>

#include "glad/glad.h"

static int getTextureFormat(int32_t numComponents) {
  switch (numComponents) {
    default:
      return GL_RGBA;
    case 3:
      return GL_RGB;
    case 2:
      return GL_RG;
    case 1:
      return GL_RED;
  }
}

namespace ld55 {
uint32_t Texture::loadTexture(const void *data, uint32_t width, uint32_t height,
                              int32_t wrapMode, int32_t magFilter,
                              int32_t minFilter, bool mipmap) {
  uint32_t texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  int format = GL_RGBA;
  glTexImage2D(GL_TEXTURE_2D, 0, format, (GLsizei)width, (GLsizei)height, 0, format,
               GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

  // Black border by default
  float borderColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

  if (mipmap) {
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  glBindTexture(GL_TEXTURE_2D, 0);
  return texture;
}

Texture::Texture(const void *data, uint32_t width, uint32_t height, int32_t wrapMode, int32_t magFilter,
                 int32_t minFilter, bool mipmap) {
  id = loadTexture(data, width, height, wrapMode, magFilter, minFilter, mipmap);
}

void Texture::bindToTextureUnit(uint32_t unit) {
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, getId());
  glBindTextureUnit(unit, getId());
}

Texture::Texture(const void *data, uint32_t width, uint32_t height) {
  id = loadTexture(data, width, height, GL_REPEAT, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, true);
}
}  // namespace ld55