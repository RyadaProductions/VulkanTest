#include "Engine.hxx"

// public
void Engine::run() {
	initWindow();
	initVulkan();
	mainLoop();
	cleanup();
}

// private
void Engine::initWindow() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_NO_API);

	window = glfwCreateWindow(settings.WIDTH, settings.HEIGHT, "Vulkan", nullptr, nullptr);
}

void Engine::initVulkan() {
	// Create vulkan instance
	vulkanInstance.initInstance(&settings);
	// Setup the debug messenger
	debugManager.setupDebugMessenger(&settings, vulkanInstance.instance);
	// Create vulkan surface
	createSurface();
	// Pick physical device
	physicalDevice.pickPhysicalDevice(vulkanInstance.instance, surface, &settings);
	// Create logical device
	logicalDevice.createLogicalDevice(physicalDevice.physicalDevice, surface, &settings);
	// Create swap chain
	swapChain.createSwapChain(physicalDevice.physicalDevice, logicalDevice.device, surface, &settings);
  // Create image views
  swapChain.createImageViews(logicalDevice.device);
}

void Engine::mainLoop() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
}

void Engine::cleanup() {
  for (auto imageView : swapChain.swapChainImageViews) {
    vkDestroyImageView(logicalDevice.device, imageView, nullptr);
  }

	vkDestroySwapchainKHR(logicalDevice.device, swapChain.swapChain, nullptr);
	vkDestroyDevice(logicalDevice.device, nullptr);

	if (settings.enableValidationLayers) {
		debugManager.destroyDebugUtilsMessengerEXT(vulkanInstance.instance, debugManager.debugMessenger, nullptr);
	}

	vkDestroySurfaceKHR(vulkanInstance.instance, surface, nullptr);
	vkDestroyInstance(vulkanInstance.instance, nullptr);

	glfwDestroyWindow(window);

	glfwTerminate();
}

void Engine::createSurface() {
	if (glfwCreateWindowSurface(vulkanInstance.instance, window, nullptr, &surface) != VK_SUCCESS)
		throw std::runtime_error("Failed to create window surface!");
}
