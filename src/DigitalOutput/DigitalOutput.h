#ifndef DigitalOutput_h
#define DigitalOutput_h
#pragma once
#include "Pin.h"

// Class to manage digital output

class DigitalOutput {
private:
  Pin* pin;
  bool active;

public:
  // Initialise a digital output to a pin and a state false = LOW (default), true = HIGH
  DigitalOutput(Pin*, bool = false);
  void on();
  void off();
  void toggle();
  bool isActive();
};

#endif
