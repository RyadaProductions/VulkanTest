#ifndef VulkanRenderPipeline_H
#define VulkanRenderPipeline_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <fstream>

#include "VulkanRenderPass.hxx"

class VulkanRenderPipeline {
public:
	VkPipelineLayout pipelineLayout;

	VkPipeline graphicsPipeline;

	void createGraphicsPipeline(VkDevice device, VkRenderPass renderPass, VkExtent2D swapChainExtent);

private:
	std::vector<char> readFile(const std::string& fileName);

	VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);
};

#endif // !VulkanRenderPipeline_H