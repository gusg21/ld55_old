//
// Created by angus.goucher on 4/9/2024.
//

#include "ld55/renderer.h"

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include <glm/glm.hpp>

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

ld55::Renderer::Renderer(const void *window_handle, uint32_t width,
                         uint32_t height) {
  // Load OpenGL Context
  SDL_GL_LoadLibrary(nullptr);
  context_ = SDL_GL_CreateContext((SDL_Window *)window_handle);
  if (context_ == nullptr) {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
                    "Failed to create OpenGL context: %s", SDL_GetError());
    return;
  }

  // Load OpenGL
  int version = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
  if (version == 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
                    "Failed to initialize OpenGL context");
    return;
  }

  // Configure Quad VAO
  unsigned int VBO;
  float vertices[] = {
      // pos      // tex
      0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

      0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f};

  glGenVertexArrays(1, &this->quad_vao_);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(this->quad_vao_);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);  // Depth testing
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));

  width_ = width;
  height_ = height;
}

ld55::Shader ld55::Renderer::CreateShader(const char *vertexSource,
                                          const char *fragmentSource) {
  printf("VERT:\n%s\n\nFRAG:\n%s\n", vertexSource, fragmentSource);
  return {std::string(vertexSource), std::string(fragmentSource)};
}

void ld55::Renderer::SetSpriteShader(const ld55::Shader *shader) {
  this->sprite_shader_ = shader;
}

void ld55::Renderer::DrawSprite(ld55::Texture &tex, glm::vec2 position,
                                glm::vec2 size, float rotate, glm::vec3 color) {
  this->sprite_shader_->use();

  auto model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(position, 0.0f));

  model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
  model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
  model =
      glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

  model = glm::scale(model, glm::vec3(size, 1.0f));

  this->sprite_shader_->setMat4("model", model);
  this->sprite_shader_->setMat4("project", GetProjection());
  this->sprite_shader_->setInt("image", (int)tex.getId());
  this->sprite_shader_->setVec3("spriteColor", color);

  glActiveTexture(GL_TEXTURE0);
  tex.bind();

  glBindVertexArray(this->quad_vao_);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

glm::mat4 ld55::Renderer::GetProjection() {
  return glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
}

void ld55::Renderer::Clear() {
  glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
