#ifndef VulkanInstance_H
#define VulkanInstance_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>

#include "Settings.h"

class VulkanInstance {
public:
	VkInstance instance;

	void initInstance(Settings* settings);

private:
	bool isInitialized;

	void outputAvailableExtensions(std::vector<const char*>* pRequiredExtensions);

	bool checkValidationLayerSupport(Settings* settings);

	std::vector<const char*> getRequiredExtensions(Settings* settings);
};
#endif // !VulkanInstance_H