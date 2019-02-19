#include "VulkanPhysicalDevice.hxx"

void VulkanPhysicalDevice::pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface, Settings* pSettings) {
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if (deviceCount == 0)
		throw std::runtime_error("No GPU with Vulkan support found!");

	std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, physicalDevices.data());

	for (const auto& device : physicalDevices) {
		if (!isDeviceSuitable(device, surface, pSettings)) continue;

		physicalDevice = device;
	}

	if (physicalDevice == VK_NULL_HANDLE)
		throw std::runtime_error("Failed to find a suitable GPU");
}

bool VulkanPhysicalDevice::isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface, Settings* pSettings) {
	QueueFamilyIndices indices = findQueueFamilies(device, surface);

  bool extensionsSupported = checkDeviceExtensionSupport(device, pSettings);
  bool swapChainSupportAdequate;

  if (extensionsSupported) {
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device, surface);
    swapChainSupportAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
  }

	return indices.isComplete() && extensionsSupported && swapChainSupportAdequate;
}

bool VulkanPhysicalDevice::checkDeviceExtensionSupport(VkPhysicalDevice device, Settings* pSettings) {
  uint32_t extensionCount;
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

  std::vector<VkExtensionProperties> availableExtensions(extensionCount);
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

  std::set<std::string> requiredExtensions(pSettings->deviceExtensions.begin(), pSettings->deviceExtensions.end());

  for (const auto& extension : availableExtensions) {
    requiredExtensions.erase(extension.extensionName);
  }

  return requiredExtensions.empty();
}