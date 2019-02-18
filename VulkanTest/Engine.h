#ifndef HelloTriangleApplication_H
#define HelloTriangleApplication_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

// h files
#include "VulkanInstance.h"
#include "QueueFamilyIndices.h"
#include "Settings.h"
#include "DebugManager.h"

class Engine {
public:
	void run();

private:
	GLFWwindow* window;

	VulkanInstance vulkanInstance;
	VkDebugUtilsMessengerEXT debugMessenger;

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;
	VkQueue graphicsQueue;

	Settings settings;
	DebugManager debugManager;

	void initWindow();
	void initVulkan();
	void mainLoop();
	void cleanup();

	void createInstance();
	void setupDebugManager();
	void pickPhysicalDevice();

	void createLogicalDevice();

	bool isDeviceSuitable(VkPhysicalDevice device);

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
};
#endif // !HelloTriangleApplication_H