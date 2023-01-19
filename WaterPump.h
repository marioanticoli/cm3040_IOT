#ifndef WaterPump_h
#define WaterPump_h
#include "Arduino.h" 

class WaterPump {
private:
  uint8_t pin;

public:
  WaterPump(uint8_t);
  void on();
  void off();
};
#endif
