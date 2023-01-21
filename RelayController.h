#ifndef RelayController_h
#define RelayController_h
#include "Arduino.h"

class RelayController {
private:
  uint8_t pin;
  bool active;

public:
  // Initialise a relay to pin
  RelayController(uint8_t);
  // Switch relay on
  void on();
  // Switch relay off
  void off();
  // Toggle relay state
  void toggle();
};
#endif
