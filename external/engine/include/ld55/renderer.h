#pragma once

#include <SDL3/SDL.h>

#include <ld55/shader.h>

namespace ld55 {
class Renderer {
 public:
  explicit Renderer(const void* window_handle);

  ld55::Shader CreateShader(const char* vertexSource, const char* fragmentSource);

 private:
  SDL_GLContext context_;
};
}  // namespace ld55