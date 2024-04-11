#pragma once

namespace ld55 {
class Window {
public:
  virtual void Open() = 0;
  virtual bool HandleEvents() = 0;
  virtual void* GetWindowHandle() = 0;
  virtual void Present() = 0;
};
} // namespace ld55
