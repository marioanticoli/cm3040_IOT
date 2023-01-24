#ifndef NCRelayController_h
#define NCRelayController_h
#include "Arduino.h"
#include "RelayController.h"

// NC implementation of RelayController

class NCRelayController : public RelayController {
public:
  // Initialise a relay to pin
  NCRelayController(uint8_t);
  // Switch relay on
  void on() override;
  // Switch relay off
  void off() override;
};

#endif
