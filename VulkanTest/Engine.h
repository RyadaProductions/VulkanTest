#ifndef HelloTriangleApplication_H
#define HelloTriangleApplication_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

// h files
#include "QueueFamilyIndices.h"
#include "Settings.h"
#include "DebugManager.h"

class Engine {
public:
  void run();

private:
  GLFWwindow* window;

  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;

  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkDevice device;
  VkQueue graphicsQueue;

  Settings settings;
  DebugManager debugManager;

  void initWindow();
  void initVulkan();
  void mainLoop();
  void cleanup();

  void createInstance();
  void setupDebugManager();
  void pickPhysicalDevice();

  void createLogicalDevice();

  bool checkValidationLayerSupport();
  void outputAvailableExtensions(std::vector<const char*>* pRequiredExtensions);
  std::vector<const char*> getRequiredExtensions();
  bool isDeviceSuitable(VkPhysicalDevice device);

  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
};
#endif // !HelloTriangleApplication_H