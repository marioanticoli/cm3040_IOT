#include "NCRelayController.h"
#include "Arduino.h"
#include "DigitalPin.h"

NCRelayController::NCRelayController(Pin* pin)
  : RelayController(pin) {
    pin->doPinMode(OUTPUT);
    off();
  }

NCRelayController::NCRelayController(uint8_t pin)
  : NCRelayController(new DigitalPin(pin)) {
    this->pin->doPinMode(OUTPUT);
  }

void NCRelayController::on() {
  if (!active) {
    pin->doWrite(HIGH);
    active = true;
  }
};

void NCRelayController::off() {
  if (active) {
    pin->doWrite(LOW);
    active = false;
  }
};
