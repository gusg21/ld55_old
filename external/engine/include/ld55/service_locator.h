#pragma once

#include <memory>

#include <ld55/platform/window.h>
#include <ld55/assets.h>


namespace ld55 {
class ServiceLocator {
public:
  static inline const std::unique_ptr<Window> &GetWindow() { return window_; }
  static inline const std::unique_ptr<Assets> &GetAssets() { return assets_; }

  static inline void Provide(Window *window) {
    if (window_ != nullptr)
      return;
    window_ = std::unique_ptr<Window>(window);
  }

  static inline void Provide(Assets *assets) {
    if (assets_ != nullptr)
      return;
    assets_ = std::unique_ptr<Assets>(assets);
  }

private:
  static inline std::unique_ptr<Window> window_ = nullptr;
  static inline std::unique_ptr<Assets> assets_ = nullptr;
};
} // namespace ld55