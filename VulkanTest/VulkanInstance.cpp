#include "VulkanInstance.hxx"

void VulkanInstance::initInstance(Settings* pSettings) {
	if (isInitialized)
		throw std::runtime_error("Vulkan instance was already initialized");

	if (pSettings->enableValidationLayers && !checkValidationLayerSupport(pSettings))
		throw std::runtime_error("Validation layers requested, but not available!");

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	std::vector<const char*> requiredExtensions = getRequiredExtensions(pSettings);
	createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
	createInfo.ppEnabledExtensionNames = requiredExtensions.data();

	if (pSettings->enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(pSettings->validationLayers.size());
		createInfo.ppEnabledLayerNames = pSettings->validationLayers.data();
	}
	else
		createInfo.enabledLayerCount = 0;

	outputAvailableExtensions(&requiredExtensions);

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
		throw std::runtime_error("Failed to create a Vulkan instance!");

	isInitialized = true;
}

void VulkanInstance::outputAvailableExtensions(std::vector<const char*> * pRequiredExtensions) {
	uint32_t availableExtensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, nullptr);
	std::vector<VkExtensionProperties> availableExtensions(availableExtensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, availableExtensions.data());

	std::cout << "available extensions:" << std::endl;
	for (const auto& availableExtension : availableExtensions) {
		std::cout << "\t" << availableExtension.extensionName;

		bool isAvailable = false;
		for (uint32_t i = 0; i < static_cast<uint32_t>(pRequiredExtensions->size()); i++) {
			if (strcmp(pRequiredExtensions->at(i), availableExtension.extensionName) != 0) continue;
			isAvailable = true;
		}
		std::cout << "\t" << (isAvailable ? "Required" : "Not required") << std::endl;
	}
}

bool VulkanInstance::checkValidationLayerSupport(Settings * pSettings) {
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
	if (layerCount > 0)
		std::cout << "Looking for instance layers: " << std::endl;

	for (const char* layerName : pSettings->validationLayers) {
		bool layerFound = false;
		std::cout << "\t" << layerName;

		for (const auto& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) != 0) continue;

			std::cout << "\tfound" << std::endl;
			layerFound = true;
			break;
		}

		if (!layerFound)
			return false;
	}

	return true;
}

std::vector<const char*> VulkanInstance::getRequiredExtensions(Settings * pSettings) {
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (pSettings->enableValidationLayers)
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	return extensions;
}