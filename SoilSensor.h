#ifndef SoilSensor_h
#define SoilSensor_h
#include "Arduino.h"

class SoilSensor {
private:
  int pin;

public:
  SoilSensor(int pin);
  long get_humidity();
};
#endif
