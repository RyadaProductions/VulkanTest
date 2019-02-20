#ifndef Settings_H
#define Settings_H

#include <vector>

class Settings {
public:
	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;

	const std::vector<const char*> validationLayers = {
	  "VK_LAYER_LUNARG_standard_validation"
	};

  const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
  };

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif 

private:
};

#endif // !Globals_H