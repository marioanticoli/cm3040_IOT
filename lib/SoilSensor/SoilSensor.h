#ifndef SoilSensor_h
#define SoilSensor_h
#include "Arduino.h" 

class SoilSensor {
public:
  SoilSensor(int pin);
  int get_humidity();
  void print();
private:
  int pin;
};
#endif
