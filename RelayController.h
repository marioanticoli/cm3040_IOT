#ifndef RelayController_h
#define RelayController_h
#include "Arduino.h"

// Abstract class for controlling relays

class RelayController {
protected:
  uint8_t pin;
  bool active;

public:
  // Initialise a relay to pin
  RelayController(uint8_t);
  // Toggle relay state
  void toggle();
  // Verify the state of the relay
  bool isActive();
  // Switch relay on
  virtual void on() = 0;
  // Switch relay off
  virtual void off() = 0;
};
#endif
