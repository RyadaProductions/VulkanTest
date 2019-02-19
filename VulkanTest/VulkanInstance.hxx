#ifndef VulkanInstance_H
#define VulkanInstance_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>

#include "Settings.hxx"

class VulkanInstance {
public:
	VkInstance instance;

	void initInstance(Settings* settings);

private:
	bool isInitialized;

	void outputAvailableExtensions(std::vector<const char*>* pRequiredExtensions);

	bool checkValidationLayerSupport(Settings* pSettings);

	std::vector<const char*> getRequiredExtensions(Settings* pSettings);
};
#endif // !VulkanInstance_H