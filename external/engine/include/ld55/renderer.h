#pragma once

#include <SDL3/SDL.h>
#include <ld55/shader.h>
#include <ld55/texture.h>

namespace ld55 {
class Renderer {
 public:
  explicit Renderer(const void* window_handle, uint32_t width, uint32_t height);

  ld55::Shader CreateShader(const char* vertexSource, const char* fragmentSource);
  void SetSpriteShader(const ld55::Shader* shader);
  void DrawSprite(Texture& tex, glm::vec2 position, glm::vec2 size,
                  float rotate, glm::vec3 color);
  void Clear();
  glm::mat4 GetProjection();

 private:
  SDL_GLContext context_;
  uint32_t width_, height_;
  uint32_t quad_vao_;
  const ld55::Shader* sprite_shader_;

};
}  // namespace ld55