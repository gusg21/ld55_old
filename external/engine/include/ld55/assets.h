#pragma once

#include <string>
#include <vector>
#include <map>

namespace ld55 {
struct AssetHandle {
  uint32_t start_block;
  uint32_t block_count;
  uint32_t byte_count;
};

class Assets {
 public:
  Assets() = default;
  explicit Assets(const std::string& can_file);

  const AssetHandle* findAssetHandle(const std::string& name);
  const char* getAssetData(const AssetHandle& handle);

 private:
  uint32_t block_count_ = 0;
  char* data_ = nullptr;
  std::map<std::string, AssetHandle> assets_;
};
}  // namespace ld55
