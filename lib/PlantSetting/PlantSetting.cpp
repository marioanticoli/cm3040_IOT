#include "PlantSetting.h"

uint8_t getLuminosity() {
  return luminosity;
}

void setLuminosity(uint8_t luminosity) {
  this->luminosity = luminosity;
}

uint8_t getHumidity() {
  return humidity;
}

void setHumidity(uint8_t humidity) {
  this->humidity = humidity;
}

