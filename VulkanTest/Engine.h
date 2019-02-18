#ifndef HelloTriangleApplication_H
#define HelloTriangleApplication_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// h files
#include "VulkanInstance.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanLogicalDevice.h"
#include "Settings.h"
#include "DebugManager.h"

class Engine {
public:
	void run();

private:
	GLFWwindow* window;

	VulkanInstance vulkanInstance;
	VkDebugUtilsMessengerEXT debugMessenger;

	VulkanPhysicalDevice physicalDevice;
	VulkanLogicalDevice logicalDevice;

	Settings settings;
	DebugManager debugManager;

	void initWindow();
	void initVulkan();
	void mainLoop();
	void cleanup();
};
#endif // !HelloTriangleApplication_H