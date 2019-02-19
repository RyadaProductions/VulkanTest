#include "VulkanPhysicalDevice.hxx"

void VulkanPhysicalDevice::pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface) {
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if (deviceCount == 0)
		throw std::runtime_error("No GPU with Vulkan support found!");

	std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, physicalDevices.data());

	for (const auto& device : physicalDevices) {
		if (!isDeviceSuitable(device, surface)) continue;

		physicalDevice = device;
	}

	if (physicalDevice == VK_NULL_HANDLE)
		throw std::runtime_error("Failed to find a suitable GPU");
}

bool VulkanPhysicalDevice::isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface) {
	QueueFamilyIndices indices = findQueueFamilies(device, surface);

	return indices.isComplete();
}