#pragma once

namespace ld55 {
class Window {
public:
  virtual void Open() = 0;
  virtual bool HandleEvents() = 0;
};
} // namespace ld55
