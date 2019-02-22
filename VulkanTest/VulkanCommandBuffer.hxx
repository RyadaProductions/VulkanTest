#ifndef VulkanCommandBuffer_H
#define VulkanCommandBuffer_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>

#include "QueueFamilyIndices.hxx"

class VulkanCommandBuffer {
public:
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;

	void createCommandPool(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);

	void createCommandBuffers(VkDevice device, VkRenderPass renderPass, VkExtent2D swapChainExtent, VkPipeline graphicsPipeline, std::vector<VkFramebuffer> swapChainFramebuffers);
private:

};
#endif // !VulkanCommandBuffer_H