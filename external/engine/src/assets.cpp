#include "ld55/assets.h"

#include <fstream>
#include <memory>
#include <iostream>

#define BLOCK_SIZE 512

using namespace ld55;

static void ReadNullTerminated(std::ifstream &stream, char *buf) {
  char c;
  stream.read(&c, 1);
  int32_t index = 0;
  while (c != '\0') {
    buf[index] = c;
    index++;
    stream.read(&c, 1);
  }
}

Assets::Assets(const std::string &can_file) {
  std::ifstream can_stream(can_file);

  char can_magic[4];
  can_stream.read(can_magic, 4);
  if (!(can_magic[0] == 'C' && can_magic[1] == 'A' && can_magic[2] == 'N' &&
        can_magic[3] == '!')) {
    printf("Malformed can file header!\n");
    return;
  }

  int32_t can_index_size = 0;
  can_stream.read((char *)&can_index_size,
                  4);  // pretend the int is a char array

  // Load the index
  data_size_ = 0;
  for (int32_t i = 0; i < can_index_size; i++) {
    char name[512] = {0};
    ReadNullTerminated(can_stream, name);

    uint32_t start_byte, byte_count;
    can_stream.read((char *)&start_byte, 4);
    can_stream.read((char *)&byte_count, 4);
    printf("%s starts at byte %d, %d bytes\n", name, start_byte, byte_count);

    assets_[name] = {.start_byte = start_byte,
                     .byte_count = byte_count};

    data_size_ += byte_count;
  }

  // Allocate the data block
  data_ = new unsigned char[data_size_];

  // Read the data
  can_stream.read(
        (char *)&data_,  // I love pointer arithmetic!
        data_size_);
}

const unsigned char *Assets::GetAssetData(const AssetHandle *handle) {
  printf("Getting asset @ offset %d\n", handle->start_byte);
  const unsigned char *data_ptr = &(data_[handle->start_byte]);
  return data_ptr;
}

const AssetHandle *Assets::FindAssetHandle(const std::string &name) {
  auto entry = assets_.find(name);
  if (entry == assets_.end()) return nullptr;
  return &entry->second;
}
