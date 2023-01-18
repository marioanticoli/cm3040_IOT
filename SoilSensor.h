#ifndef SoilSensor_h
#define SoilSensor_h
#include "Arduino.h"

class SoilSensor {
private:
  uint pin;

public:
  SoilSensor(uint pin);
  long get_humidity();
};
#endif
