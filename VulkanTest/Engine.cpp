#include "Engine.h"

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
	createInstance();
	setupDebugManager();
	pickPhysicalDevice();
	createLogicalDevice();
}

void Engine::mainLoop() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
}

void Engine::cleanup() {
	vkDestroyDevice(logicalDevice.device, nullptr);

	if (settings.enableValidationLayers) {
		debugManager.destroyDebugUtilsMessengerEXT(vulkanInstance.instance, debugMessenger, nullptr);
	}

	vkDestroyInstance(vulkanInstance.instance, nullptr);

	glfwDestroyWindow(window);

	glfwTerminate();
}

void Engine::createInstance() {
	vulkanInstance.initInstance(&settings);
}

void Engine::pickPhysicalDevice() {
	physicalDevice.pickPhysicalDevice(vulkanInstance.instance);
}

void Engine::setupDebugManager() {
	debugManager.setupDebugMessenger(&settings, vulkanInstance.instance, &debugMessenger);
}

void Engine::createLogicalDevice() {
	logicalDevice.createLogicalDevice(physicalDevice.physicalDevice, &settings);
}
