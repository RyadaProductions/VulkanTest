#ifndef VulkanSwapChain_H
#define VulkanSwapChain_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <algorithm>
#include <stdexcept>

#include "SwapChainSupportDetails.hxx"
#include "QueueFamilyIndices.hxx"
#include "Settings.hxx"

class VulkanSwapChain {
public:
	SwapChainSupportDetails swapChainSupport;

	VkSwapchainKHR swapChain;

	VkSurfaceFormatKHR surfaceFormat;
	VkPresentModeKHR presentMode;
	VkExtent2D extent;

	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;

	void createSwapChain(VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface, GLFWwindow* window, Settings* pSettings);

	void createImageViews(VkDevice device);

private:
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);

	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window, Settings* pSettings);
};

#endif // !VulkanSwapChain_H