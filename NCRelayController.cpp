#include "NCRelayController.h"

NCRelayController::NCRelayController(uint8_t pin)
  : RelayController(pin) {}

void NCRelayController::on() {
  if (!active) {
    digitalWrite(pin, LOW);
    active = true;
  }
};

void NCRelayController::off() {
  if (active) {
    digitalWrite(pin, HIGH);
    active = false;
  }
};
