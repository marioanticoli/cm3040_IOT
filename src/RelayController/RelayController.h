#ifndef RelayController_h
#define RelayController_h
#include "Pin.h"

// Abstract class for controlling relays

class RelayController {
protected:
  Pin* pin;
  bool active;

public:
  // Initialise a relay to pin
  RelayController(Pin*);
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
