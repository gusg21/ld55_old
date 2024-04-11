#include "sdl_window.h"

#include <cstdio>

using namespace ld55;

void SDLWindow::Open() {
  window_ = SDL_CreateWindow("LD55 Engine", 1600, 900, 0);
  if (window_ == nullptr) {
    printf("Failed to create SDL Window!");
  }
}

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