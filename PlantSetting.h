#pragma once
#ifndef PlantSetting_h
#define PlantSetting_h
#include "Arduino.h"
// PlantSetting class

class PlantSetting {
private:
  uint8_t luminosity;
  uint8_t humidity;

public:
  // Get the luminosity
  uint8_t getLuminosity();
  // Set the luminosity
  void incLuminosity(int8_t);
  // Get the humidity
  uint8_t getHumidity();
  // Set the humidity
  void incHumidity(int8_t);
};

#endif
