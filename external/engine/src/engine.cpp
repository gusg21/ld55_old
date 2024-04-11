#include "ld55/engine.h"

#include <ld55/service_locator.h>

#include <cstdio>

#include "ld55/assets.h"
#include "platform/sdl_window.h"

using namespace ld55;

void Engine::Init(const std::string& can_file) {
  // SDL setup
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Failed to initialize SDL: %s",
                    SDL_GetError());
    return;
  }

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  ServiceLocator::Provide(new SDLWindow(1600, 900));
  ServiceLocator::Provide(new Assets(can_file));
  ServiceLocator::Provide(
      new Renderer(ServiceLocator::GetWindow()->GetWindowHandle(), 1600, 900));
}