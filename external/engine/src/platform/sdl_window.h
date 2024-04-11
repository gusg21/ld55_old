#pragma once

#include <SDL3/SDL.h>

#include <ld55/platform/window.h>

namespace ld55 {
class SDLWindow : public Window {
public:
  SDLWindow() = default;
  virtual void Open() override;
  virtual bool HandleEvents() override;

private:
  SDL_Window *window_ = nullptr;
};
} // namespace ld55
