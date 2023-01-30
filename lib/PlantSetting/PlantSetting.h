#pragma once
#ifndef PlantSetting_h
#define PlantSetting_h

// PlantSetting class

class PlantSetting {
private:
  uint8_t luminosity,
          humidity;

public:
  // Get the luminosity
  uint8_t getLuminosity();
  // Set the luminosity
  void setLuminosity(uint8_t);
  // Get the humidity
  uint8_t getHumidity();
  // Set the humidity
  void setHumidity(uint8_t);
};

#endif
