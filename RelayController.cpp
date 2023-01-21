#include "RelayController.h"

// Class to control a 3 pin relay in

RelayController::RelayController(uint8_t pin)
  : pin(pin) {

  pinMode(pin, OUTPUT);
  active = false;
};

void RelayController::on() {
  if (!active) {
    digitalWrite(pin, LOW);
    active = true;
  }
};

void RelayController::off() {
  if (active) {
    digitalWrite(pin, HIGH);
    active = false;
  }
};

void RelayController::toggle() {
  if (active) {
    off();
  } else {
    on();
  }
};
