#ifndef VulkanRenderPass_H
#define VulkanRenderPass_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>

class VulkanRenderPass {
public:
	VkRenderPass renderPass;

	void createRenderPass(VkDevice device, VkFormat swapChainImageFormat);

private:

};

#endif // !VulkanRenderPass_H