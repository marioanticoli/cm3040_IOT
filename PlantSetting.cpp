#include "PlantSetting.h"

uint8_t PlantSetting::getLuminosity() {
  return luminosity;
}

void PlantSetting::incLuminosity(int8_t val) {
  if(luminosity + val <= 100 && luminosity + val >= 0) {
    luminosity += val;
  }
}

uint8_t PlantSetting::getHumidity() {
  return humidity;
}

void PlantSetting::incHumidity(int8_t val) {
  if(humidity + val <= 100 && humidity + val >= 0) {
    humidity += val;
  }
}

