#include "RelayController.h"

// Work with 3 pin relay
// mode controls NO(=true), NC(=false)
RelayController::RelayController(uint8_t pin, bool mode)
  : pin(pin), mode(mode) {

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

void RelayController::write() {
}

