#ifndef WaterPump_h
#define WaterPump_h
#include "Arduino.h" 

class WaterPump {
public:
  WaterPump(int pin);
  void on();
  void off();
private:
  int pin;
};
#endif
