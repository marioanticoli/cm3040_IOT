#ifndef NCRelayController_h
#define NCRelayController_h
#pragma once
#include "RelayController.h"
#include "Pin.h"

// NC implementation of RelayController

class NCRelayController : public RelayController {
public:
  // Initialise a relay to pin
  NCRelayController(Pin*);
  // Switch relay on
  void on() override;
  // Switch relay off
  void off() override;
};

#endif
