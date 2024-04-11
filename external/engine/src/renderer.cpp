//
// Created by angus.goucher on 4/9/2024.
//

#include "ld55/renderer.h"

#include <SDL3/SDL.h>
#include <glad/glad.h>

ld55::Renderer::Renderer(const void* window_handle) {
  // Load OpenGL Context
  SDL_GL_LoadLibrary(nullptr);
  context_ = SDL_GL_CreateContext((SDL_Window*)window_handle);
  if (context_ == nullptr) {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
                    "Failed to create OpenGL context: %s",
                    SDL_GetError());
    return;
  }

  // Load OpenGL
  int version = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
  if (version == 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
                    "Failed to initialize OpenGL context");
    return;
  }
}

ld55::Shader ld55::Renderer::CreateShader(const char *vertexSource,
                                          const char *fragmentSource) {
  return { std::string(vertexSource), std::string(fragmentSource) };
}
