#include "VulkanPhysicalDevice.h"

void VulkanPhysicalDevice::pickPhysicalDevice(VkInstance instance) {
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if (deviceCount == 0)
		throw std::runtime_error("No GPU with Vulkan support found!");

	std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, physicalDevices.data());

	for (const auto& device : physicalDevices) {
		if (!isDeviceSuitable(device)) continue;

		physicalDevice = device;
	}

	if (physicalDevice == VK_NULL_HANDLE)
		throw std::runtime_error("Failed to find a suitable GPU");
}

bool VulkanPhysicalDevice::isDeviceSuitable(VkPhysicalDevice device) {
	QueueFamilyIndices indices = findQueueFamilies(device);

	return indices.isComplete();
}