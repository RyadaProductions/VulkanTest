#include "VulkanFrameBuffer.hxx"

void VulkanFramebuffer::createFramebuffers(VkDevice device, VkExtent2D extent, VkRenderPass renderPass, std::vector<VkImageView> swapChainImageViews) {
  swapChainFramebuffers.resize(swapChainImageViews.size());

  for (uint32_t i = 0; i < swapChainImageViews.size(); i++) {
    VkImageView attachments[] = {
      swapChainImageViews[i]
    };

    VkFramebufferCreateInfo frameBufferInfo = {};
    frameBufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    frameBufferInfo.renderPass = renderPass;
    frameBufferInfo.attachmentCount = 1;
    frameBufferInfo.pAttachments = attachments;
    frameBufferInfo.width = extent.width;
    frameBufferInfo.height = extent.height;
    frameBufferInfo.layers = 1;

    if (vkCreateFramebuffer(device, &frameBufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
      throw std::runtime_error("Could not create framebuffers!");
    }
  }
}