#ifndef Settings_H
#define Settings_H

#include <vector>

class Settings {
public:
  const int WIDTH = 800;
  const int HEIGHT = 600;

  const std::vector<const char*> validationLayers = {
    "VK_LAYER_LUNARG_standard_validation"
  };

#ifdef NDEBUG
  const bool enableValidationLayers = false;
#else
  const bool enableValidationLayers = true;
#endif 

private:
};

#endif // !Globals_H