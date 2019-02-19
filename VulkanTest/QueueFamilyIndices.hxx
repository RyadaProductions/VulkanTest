#ifndef QueueFamilyIndices_H
#define QueueFamilyIndices_H

#include <optional>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;

	bool isComplete() {
		return graphicsFamily.has_value();
	}
};

static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
	QueueFamilyIndices indices;

	uint32_t indicesCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &indicesCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(indicesCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &indicesCount, queueFamilies.data());

	int i = 0;
	for (const auto& family : queueFamilies) {
		if (family.queueCount > 0 && family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}

		if (indices.isComplete())
			break;

		i++;
	}

	return indices;
}
#endif // !QueueFamilyIndices_H