#include "VulkanLogicalDevice.hxx"

void VulkanLogicalDevice::createLogicalDevice(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, Settings* settings) {
	QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface);

	VkDeviceQueueCreateInfo queueCreateInfo = {};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
	queueCreateInfo.queueCount = 1;

	float queuePriority = 1.0f;
	queueCreateInfo.pQueuePriorities = &queuePriority;

	VkPhysicalDeviceFeatures deviceFeatures = {};

	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;
	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = 0;

	if (settings->enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(settings->validationLayers.size());
		createInfo.ppEnabledLayerNames = settings->validationLayers.data();
	}
	else
		createInfo.enabledLayerCount = 0;

	if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
		throw std::runtime_error("Failed to create logical device");

	vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
}