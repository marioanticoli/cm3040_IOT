#include "PlantSetting.h"

uint8_t PlantSetting::getLuminosity() {
  return luminosity;
}

void PlantSetting::incLuminosity(int8_t val) {
  if (checkLimits(luminosity, val)) {
    luminosity += val;
  }
}

void PlantSetting::setLuminosity(uint8_t val) {
  if (checkLimits(0, val)) {
    luminosity = val;
  }
}

uint8_t PlantSetting::getHumidity() {
  return humidity;
}

void PlantSetting::incHumidity(int8_t val) {
  if (checkLimits(humidity, val)) {
    humidity += val;
  }
}

void PlantSetting::setHumidity(uint8_t val) {
  if (checkLimits(0, val)) {
    humidity = val;
  }
}

bool PlantSetting::checkLimits(uint8_t original, int8_t val) {
  // returns true if between 0 and 100 percent included
  return ((original + val) <= 100) && ((original + val) >= 0);
}
