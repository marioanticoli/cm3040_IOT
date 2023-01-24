#include "NCRelayController.h"

NCRelayController::NCRelayController(Pin* pin)
  : RelayController(pin) {}

void NCRelayController::on() {
  if (!active) {
    pin->doDigitalWrite(LOW);
    active = true;
  }
};

void NCRelayController::off() {
  if (active) {
    pin->doDigitalWrite(HIGH);
    active = false;
  }
};
