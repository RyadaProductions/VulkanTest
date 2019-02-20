#ifndef VulkanLogicalDevice_H
#define VulkanLogicalDevice_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <set>

#include "QueueFamilyIndices.hxx"
#include "Settings.hxx"

class VulkanLogicalDevice {
public:
	VkDevice device;

	VkQueue graphicsQueue;
  VkQueue presentQueue;

	void createLogicalDevice(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, Settings* pSettings);
};
#endif // !VulkanLogicalDevice_H