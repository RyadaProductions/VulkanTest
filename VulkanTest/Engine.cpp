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
	vulkanInstance.initInstance(&settings);
	debugManager.setupDebugMessenger(&settings, vulkanInstance.instance);
	physicalDevice.pickPhysicalDevice(vulkanInstance.instance);
	logicalDevice.createLogicalDevice(physicalDevice.physicalDevice, &settings);
}

void Engine::mainLoop() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
}

void Engine::cleanup() {
	vkDestroyDevice(logicalDevice.device, nullptr);

	if (settings.enableValidationLayers) {
		debugManager.destroyDebugUtilsMessengerEXT(vulkanInstance.instance, debugManager.debugMessenger, nullptr);
	}

	vkDestroyInstance(vulkanInstance.instance, nullptr);

	glfwDestroyWindow(window);

	glfwTerminate();
}
