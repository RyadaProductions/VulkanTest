#ifndef HelloTriangleApplication_H
#define HelloTriangleApplication_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// h files
#include "VulkanInstance.hxx"
#include "VulkanPhysicalDevice.hxx"
#include "VulkanLogicalDevice.hxx"
#include "VulkanSwapChain.hxx"
#include "VulkanRenderPass.hxx"
#include "VulkanRenderPipeline.hxx"
#include "VulkanFrameBuffer.hxx"
#include "Settings.hxx"
#include "DebugManager.hxx"

class Engine {
public:
	void run();

private:
	GLFWwindow* window;

	VulkanInstance vulkanInstance;
	VkDebugUtilsMessengerEXT debugMessenger;

	VulkanPhysicalDevice physicalDevice;
	VulkanLogicalDevice logicalDevice;
  VulkanSwapChain swapChain;
  VulkanRenderPass renderPass;
  VulkanRenderPipeline renderPipeline;
  VulkanFramebuffer framebuffer;

	Settings settings;
	DebugManager debugManager;

  VkSurfaceKHR surface;

	void initWindow();
	void initVulkan();
	void mainLoop();
	void cleanup();

  void createSurface();
};
#endif // !HelloTriangleApplication_H