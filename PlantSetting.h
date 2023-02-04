#pragma once
#ifndef PlantSetting_h
#define PlantSetting_h
#include "Arduino.h"
// PlantSetting class

class PlantSetting {
private:
  uint8_t luminosity = 50;
  uint8_t humidity = 50;
  bool checkLimits(uint8_t, int8_t);

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
