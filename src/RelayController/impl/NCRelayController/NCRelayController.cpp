#include "NCRelayController.h"
#include "Arduino.h"
#include "DigitalPin.h"

NCRelayController::NCRelayController(Pin* pin)
  : RelayController(pin) {}

NCRelayController::NCRelayController(uint8_t pin)
  : NCRelayController(new DigitalPin(pin)) {}

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
