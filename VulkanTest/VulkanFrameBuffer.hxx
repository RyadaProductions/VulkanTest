#ifndef VulkanFramebuffer_H
#define VulkanFramebuffer_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <stdexcept>

class VulkanFramebuffer {
public:
  std::vector<VkFramebuffer> swapChainFramebuffers;

  void createFramebuffers(VkDevice device, VkExtent2D extent, VkRenderPass renderPass, std::vector<VkImageView> swapChainImageViews);

private:
};

#endif // !VulkanFramebuffer_H