#ifndef DebugManager_H
#define DebugManager_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

//#include <vector>
#include <stdexcept>
#include <iostream>

#include "AnsiEscapeCodes.h"
#include "Settings.h"

class DebugManager {
public:
  void setupDebugMessenger(Settings* pSettings, VkInstance instance, VkDebugUtilsMessengerEXT* pDebugMessenger);

  void destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

private:
  VkResult createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

  static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData);
};
#endif // !DebugManager_H