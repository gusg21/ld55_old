#include "sdl_window.h"

#include <SDL3/SDL.h>

#include <cstdio>

using namespace ld55;

SDLWindow::SDLWindow(uint32_t width, uint32_t height) {
  window_ = SDL_CreateWindow("LD55 Engine", width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if (window_ == nullptr) {
    printf("Failed to create SDL Window!");
  }
}

void SDLWindow::Open() {}

bool SDLWindow::HandleEvents() {
  bool wants_close = false;

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT:
        wants_close = true;
        break;
    }
  }

  return wants_close;
}

void* SDLWindow::GetWindowHandle() { return window_; }

void SDLWindow::Present() {
  SDL_GL_SwapWindow(window_);
}
