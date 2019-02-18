#ifndef QueueFamilyIndices_H
#define QueueFamilyIndices_H

#ifndef optional_lib
#define optional_lib
#include <optional>
#endif // !optional_lib

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;

  bool isComplete() {
    return graphicsFamily.has_value();
  }
};
#endif // !QueueFamilyIndices_H