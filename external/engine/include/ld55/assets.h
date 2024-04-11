#pragma once

#include <map>
#include <string>
#include <vector>

namespace ld55 {
struct AssetHandle {
  uint32_t start_byte;
  uint32_t byte_count;
};

class Assets {
 public:
  Assets() = default;
  explicit Assets(const std::string& can_file);

  const AssetHandle* FindAssetHandle(const std::string& name);
  const char* GetAssetData(const AssetHandle* handle);

 private:
  uint32_t data_size_ = 0;
  char* data_ = nullptr;
  std::map<std::string, AssetHandle> assets_;
};
}  // namespace ld55
