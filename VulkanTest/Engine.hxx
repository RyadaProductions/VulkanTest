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
#include "VulkanCommandBuffer.hxx"
#include "Settings.hxx"
#include "DebugManager.hxx"

class Engine {
public:
	void run();

private:
	GLFWwindow* window;

	VulkanInstance vulkanInstance;
	VkDebugUtilsMessengerEXT debugMessenger;
  VkSurfaceKHR surface;

  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  std::vector<VkFence> inFlightFences;

	VulkanPhysicalDevice physicalDevice;
	VulkanLogicalDevice logicalDevice;
  VulkanSwapChain swapChain;
  VulkanRenderPass renderPass;
  VulkanRenderPipeline renderPipeline;
  VulkanFramebuffer framebuffer;
  VulkanCommandBuffer commandBuffer;

	Settings settings;
	DebugManager debugManager;

  size_t currentFrame = 0;

	void initWindow();
	void initVulkan();
	void mainLoop();
	void cleanup();

  void createSurface();
  void createSyncObjects();

  void drawFrame();
};
#endif // !HelloTriangleApplication_H