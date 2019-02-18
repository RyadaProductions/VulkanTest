#ifndef VulkanLogicalDevice_H
#define VulkanLogicalDevice_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "QueueFamilyIndices.h"
#include "Settings.h"

class VulkanLogicalDevice {
public:
	VkDevice device;
	VkQueue graphicsQueue;

	void createLogicalDevice(VkPhysicalDevice physicalDevice, Settings* settings);
};
#endif // !VulkanLogicalDevice_H