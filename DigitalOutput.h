#ifndef DigitalOutput_h
#define DigitalOutput_h
#include "Arduino.h"

// Class to manage digital output

class DigitalOutput {
private:
  uint8_t pin;
  bool state;

public:
  // Initialise a digital output to a pin and a state false = LOW (default), true = HIGH
  DigitalOutput(uint8_t, bool = false);
  void toggleState();
};
#endif
