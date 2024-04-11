#pragma once

#include <SDL3/SDL.h>

#include <ld55/platform/window.h>

namespace ld55 {
class SDLWindow : public Window {
public:
  SDLWindow(uint32_t width, uint32_t height);
  virtual void Open() override;
  virtual bool HandleEvents() override;
  virtual void* GetWindowHandle() override;
  virtual void Present() override;

private:
  SDL_Window *window_ = nullptr;
};
} // namespace ld55
