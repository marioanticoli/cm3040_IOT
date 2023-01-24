#include "DigitalOutput.h"
#include "Arduino.h"

DigitalOutput::DigitalOutput(Pin* pin, bool active)
  : pin(pin), active(active) {
  pin->doPinMode(OUTPUT);
  toggle();
};

void DigitalOutput::on() {
  if (!active) {
    pin->doWrite(HIGH);
    active = true;
  }
}

void DigitalOutput::off() {
  if (active) {
    pin->doWrite(LOW);
    active = false;
  }
};

// Change the state of the digital output; LOW -> HIGH or HIGH -> LOW
void DigitalOutput::toggle() {
  if(active) {
    off();
  } else {
    on();
  }
}

bool DigitalOutput::isActive() {
  return active;
}