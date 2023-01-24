#include "NCRelayController.h"
#include "Arduino.h"

NCRelayController::NCRelayController(Pin* pin)
  : RelayController(pin) {}

void NCRelayController::on() {
  if (!active) {
    pin->doWrite(LOW);
    active = true;
  }
};

void NCRelayController::off() {
  if (active) {
    pin->doWrite(HIGH);
    active = false;
  }
};
