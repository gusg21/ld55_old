#pragma once

#include <SDL3/SDL.h>

#include <ld55/platform/window.h>

namespace ld55 {
class SDLWindow : public Window {
public:
  SDLWindow();
  virtual void Open() override;
  virtual bool HandleEvents() override;
  virtual void* GetWindowHandle() override;

private:
  SDL_Window *window_ = nullptr;
};
} // namespace ld55
