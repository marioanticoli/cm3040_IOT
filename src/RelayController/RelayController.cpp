#include "RelayController.h"

// Class to control a 3 pin relay in

RelayController::RelayController(Pin* pin)
  : pin(pin) {

  pin->doPinMode(OUTPUT);
  active = false;
};

void RelayController::toggle() {
  if (active) {
    off();
  } else {
    on();
  }
};

bool RelayController::isActive() {
  return active;
}