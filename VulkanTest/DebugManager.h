#ifndef DebugManager_H
#define DebugManager_H

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