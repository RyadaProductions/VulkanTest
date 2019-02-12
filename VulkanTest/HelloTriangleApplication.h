#ifndef HelloTriangleApplication_H
#define HelloTriangleApplication_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>

// h files
#include "QueueFamilyIndices.h"

// impl files
#include "AnsiEscapeCodes.cpp"
#include "Globals.cpp"

class HelloTriangleApplication {
public:
  void run();

private:
  GLFWwindow* window;

  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;

  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkDevice device;
  VkQueue graphicsQueue;

  void initWindow();
  void initVulkan();
  void mainLoop();
  void cleanup();

  void createInstance();
  void setupDebugMessenger();
  void pickPhysicalDevice();

  void createLogicalDevice();

  bool checkValidationLayerSupport();
  void outputAvailableExtensions(std::vector<const char*>* pRequiredExtensions);
  std::vector<const char*> getRequiredExtensions();
  bool isDeviceSuitable(VkPhysicalDevice device);

  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

  static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData);
};
#endif // !HelloTriangleApplication_H