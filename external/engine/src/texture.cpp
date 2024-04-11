//
// Created by angus.goucher on 4/5/2024.
//

#include "ld55/texture.h"

#include <string>

#include "glad/glad.h"

static int GetTextureFormat(int32_t numComponents) {
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

static uint32_t GetIntFromBytes(const unsigned char *bytes) {
  uint32_t x = 0;

  x = (x << 8) + bytes[3];
  x = (x << 8) + bytes[2];
  x = (x << 8) + bytes[1];
  x = (x << 8) + bytes[0];

  return x;
}

namespace ld55 {
Texture::Texture(const unsigned char *data, int32_t wrapMode, int32_t magFilter,
                 int32_t minFilter, bool mipmap) {
  id = loadTexture(data, wrapMode, magFilter, minFilter, mipmap);
}

Texture::Texture(const unsigned char *data) {
  id = loadTexture(data, GL_REPEAT, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, true);
}

uint32_t Texture::loadTexture(const unsigned char *data, int32_t wrapMode,
                              int32_t magFilter, int32_t minFilter,
                              bool mipmap) {
  uint32_t width, height;
  width = GetIntFromBytes(&data[0]);
  height = GetIntFromBytes(&data[4]);

  uint32_t texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  int format = GL_RGBA;
  glTexImage2D(GL_TEXTURE_2D, 0, format, (GLsizei)width, (GLsizei)height, 0,
               format, GL_UNSIGNED_BYTE, &data[8]);
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

void Texture::bindToTextureUnit(uint32_t unit) {
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, getId());
  glBindTextureUnit(unit, getId());
}

}  // namespace ld55