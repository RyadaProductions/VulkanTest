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
	swapChain.createSwapChain(physicalDevice.physicalDevice, logicalDevice.device, surface, window, &settings);
	// Create image views
	swapChain.createImageViews(logicalDevice.device);
	// Create render passs
	renderPass.createRenderPass(logicalDevice.device, swapChain.surfaceFormat.format);
	// Create render pipeline
	renderPipeline.createGraphicsPipeline(logicalDevice.device, renderPass.renderPass, swapChain.extent);
	// Create framebuffers
	framebuffer.createFramebuffers(logicalDevice.device, swapChain.extent, renderPass.renderPass, swapChain.swapChainImageViews);
	// Create command pool
	commandBuffer.createCommandPool(logicalDevice.device, physicalDevice.physicalDevice, surface);
	// Create command buffers
	commandBuffer.createCommandBuffers(logicalDevice.device, renderPass.renderPass, swapChain.extent, renderPipeline.graphicsPipeline, framebuffer.swapChainFramebuffers);
	// Create semaphores
	createSyncObjects();
}

void Engine::mainLoop() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		drawFrame();
	}

	vkDeviceWaitIdle(logicalDevice.device);
}

void Engine::cleanup() {
	cleanupSwapChain();

	for (size_t i = 0; i < settings.MAX_FRAMES_IN_FLIGHT; i++) {
		vkDestroySemaphore(logicalDevice.device, imageAvailableSemaphores[i], nullptr);
		vkDestroySemaphore(logicalDevice.device, renderFinishedSemaphores[i], nullptr);
		vkDestroyFence(logicalDevice.device, inFlightFences[i], nullptr);
	}

	vkDestroyCommandPool(logicalDevice.device, commandBuffer.commandPool, nullptr);

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

void Engine::createSyncObjects() {
	imageAvailableSemaphores.resize(settings.MAX_FRAMES_IN_FLIGHT);
	renderFinishedSemaphores.resize(settings.MAX_FRAMES_IN_FLIGHT);
	inFlightFences.resize(settings.MAX_FRAMES_IN_FLIGHT);

	VkSemaphoreCreateInfo semaphoreInfo = {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo = {};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (size_t i = 0; i < settings.MAX_FRAMES_IN_FLIGHT; i++) {
		if (vkCreateSemaphore(logicalDevice.device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
			vkCreateSemaphore(logicalDevice.device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
			vkCreateFence(logicalDevice.device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create synchronization objects for a frame!");
		}
	}
}

void Engine::drawFrame() {
	vkWaitForFences(logicalDevice.device, 1, &inFlightFences[currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());
	vkResetFences(logicalDevice.device, 1, &inFlightFences[currentFrame]);

	uint32_t imageIndex;
	vkAcquireNextImageKHR(logicalDevice.device, swapChain.swapChain, std::numeric_limits<uint64_t>::max(), imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

	VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
	VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer.commandBuffers[imageIndex];
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	if (vkQueueSubmit(logicalDevice.graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("Failed to submit draw command buffer!");
	}

	VkSwapchainKHR swapChains[] = { swapChain.swapChain };

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr;

	vkQueuePresentKHR(logicalDevice.presentQueue, &presentInfo);

	currentFrame = (currentFrame + 1) % settings.MAX_FRAMES_IN_FLIGHT;
}

void Engine::recreateSwapChain() {
	vkDeviceWaitIdle(logicalDevice.device);

	cleanupSwapChain();

	swapChain.createSwapChain(physicalDevice.physicalDevice, logicalDevice.device, surface, window, &settings);
	swapChain.createImageViews(logicalDevice.device);
	renderPass.createRenderPass(logicalDevice.device, swapChain.surfaceFormat.format);
	renderPipeline.createGraphicsPipeline(logicalDevice.device, renderPass.renderPass, swapChain.extent);
	framebuffer.createFramebuffers(logicalDevice.device, swapChain.extent, renderPass.renderPass, swapChain.swapChainImageViews);
	commandBuffer.createCommandBuffers(logicalDevice.device, renderPass.renderPass, swapChain.extent, renderPipeline.graphicsPipeline, framebuffer.swapChainFramebuffers);
}

void Engine::cleanupSwapChain() {
	for (size_t i = 0; i < framebuffer.swapChainFramebuffers.size(); i++) {
		vkDestroyFramebuffer(logicalDevice.device, framebuffer.swapChainFramebuffers[i], nullptr);
	}

	vkFreeCommandBuffers(logicalDevice.device, commandBuffer.commandPool, static_cast<uint32_t>(commandBuffer.commandBuffers.size()), commandBuffer.commandBuffers.data());

	vkDestroyPipeline(logicalDevice.device, renderPipeline.graphicsPipeline, nullptr);
	vkDestroyPipelineLayout(logicalDevice.device, renderPipeline.pipelineLayout, nullptr);
	vkDestroyRenderPass(logicalDevice.device, renderPass.renderPass, nullptr);

	for (size_t i = 0; i < swapChain.swapChainImageViews.size(); i++) {
		vkDestroyImageView(logicalDevice.device, swapChain.swapChainImageViews[i], nullptr);
	}

	vkDestroySwapchainKHR(logicalDevice.device, swapChain.swapChain, nullptr);
}