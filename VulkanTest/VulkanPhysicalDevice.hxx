#ifndef VulkanPhysicalDevice_H
#define VulkanPhysicalDevice_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "QueueFamilyIndices.hxx"

class VulkanPhysicalDevice {
public:
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	void pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface);

private:
	bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
};
#endif // !VulkanPhysicalDevice_H