#ifndef HelloTriangleApplication_H
#define HelloTriangleApplication_H

#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#endif // !GLFW_INCLUDE_VULKAN

#ifndef iostream_lib
#define iostream_lib
#include <iostream>
#endif // !iostream_lib

#ifndef stdexcept_lib
#define stdexcept_lib
#include <stdexcept>
#endif // !stdexcept_lib

#ifndef functional_lib
#define functional_lib
#include <functional>
#endif // !functional_lib

#ifndef cstdlib_lib
#define cstdlib_lib
#include <cstdlib>
#endif // !cstdlib_lib

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