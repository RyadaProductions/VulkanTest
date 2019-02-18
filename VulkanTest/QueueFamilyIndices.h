#ifndef QueueFamilyIndices_H
#define QueueFamilyIndices_H

#include <optional>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;

	bool isComplete() {
		return graphicsFamily.has_value();
	}
};
#endif // !QueueFamilyIndices_H