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
  vkDestroyDevice(device, nullptr);

  if (settings.enableValidationLayers) {
    debugManager.destroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
  }

  vkDestroyInstance(instance, nullptr);

  glfwDestroyWindow(window);

  glfwTerminate();
}

void Engine::createInstance() {
  if (settings.enableValidationLayers && !checkValidationLayerSupport())
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

  std::vector<const char*> requiredExtensions = getRequiredExtensions();
  createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
  createInfo.ppEnabledExtensionNames = requiredExtensions.data();

  if (settings.enableValidationLayers) {
    createInfo.enabledLayerCount = static_cast<uint32_t>(settings.validationLayers.size());
    createInfo.ppEnabledLayerNames = settings.validationLayers.data();
  }
  else
    createInfo.enabledLayerCount = 0;

  outputAvailableExtensions(&requiredExtensions);

  if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
    throw std::runtime_error("Failed to create a Vulkan instance!");
}

void Engine::outputAvailableExtensions(std::vector<const char*> * pRequiredExtensions) {
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

std::vector<const char*> Engine::getRequiredExtensions() {
  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions;
  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

  if (settings.enableValidationLayers)
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

  return extensions;
}

bool Engine::checkValidationLayerSupport() {
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
  if (layerCount > 0)
    std::cout << "Looking for instance layers: " << std::endl;

  for (const char* layerName : settings.validationLayers) {
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

void Engine::pickPhysicalDevice() {
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

  if (deviceCount == 0)
    throw std::runtime_error("No GPU with Vulkan support found!");

  std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
  vkEnumeratePhysicalDevices(instance, &deviceCount, physicalDevices.data());

  for (const auto& device : physicalDevices) {
    if (!isDeviceSuitable(device)) continue;

    physicalDevice = device;
  }

  if (physicalDevice == VK_NULL_HANDLE)
    throw std::runtime_error("Failed to find a suitable GPU");
}

bool Engine::isDeviceSuitable(VkPhysicalDevice device) {
  QueueFamilyIndices indices = findQueueFamilies(device);

  return indices.isComplete();
}

QueueFamilyIndices Engine::findQueueFamilies(VkPhysicalDevice device) {
  QueueFamilyIndices indices;

  uint32_t indicesCount = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &indicesCount, nullptr);

  std::vector<VkQueueFamilyProperties> queueFamilies(indicesCount);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &indicesCount, queueFamilies.data());

  int i = 0;
  for (const auto& family : queueFamilies) {
    if (family.queueCount > 0 && family.queueFlags& VK_QUEUE_GRAPHICS_BIT) {
      indices.graphicsFamily = i;
    }

    if (indices.isComplete())
      break;

    i++;
  }

  return indices;
}

void Engine::setupDebugManager() {
  debugManager.setupDebugMessenger(&settings, instance, &debugMessenger);
}

void Engine::createLogicalDevice() {
  QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

  VkDeviceQueueCreateInfo queueCreateInfo = {};
  queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
  queueCreateInfo.queueCount = 1;

  float queuePriority = 1.0f;
  queueCreateInfo.pQueuePriorities = &queuePriority;

  VkPhysicalDeviceFeatures deviceFeatures = {};

  VkDeviceCreateInfo createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  createInfo.pQueueCreateInfos = &queueCreateInfo;
  createInfo.queueCreateInfoCount = 1;
  createInfo.pEnabledFeatures = &deviceFeatures;

  createInfo.enabledExtensionCount = 0;

  if (settings.enableValidationLayers) {
    createInfo.enabledLayerCount = static_cast<uint32_t>(settings.validationLayers.size());
    createInfo.ppEnabledLayerNames = settings.validationLayers.data();
  }
  else
    createInfo.enabledLayerCount = 0;

  if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
    throw std::runtime_error("Failed to create logical device");

  vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
}
