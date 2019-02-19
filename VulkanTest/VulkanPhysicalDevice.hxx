#ifndef VulkanPhysicalDevice_H
#define VulkanPhysicalDevice_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <set>

#include "QueueFamilyIndices.hxx"
#include "SwapChainSupportDetails.hxx"
#include "Settings.hxx"

class VulkanPhysicalDevice {
public:
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	void pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface, Settings* pSettings);

private:
	bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface, Settings* pSettings);

  bool checkDeviceExtensionSupport(VkPhysicalDevice device, Settings* pSettings);
};
#endif // !VulkanPhysicalDevice_H