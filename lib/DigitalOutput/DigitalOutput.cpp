#include "DigitalOutput.h"
#include "Arduino.h"
#include "DigitalPin.h"

DigitalOutput::DigitalOutput(Pin* pin, bool active)
  : pin(pin), active(active) {
  pin->doPinMode(OUTPUT);
  toggle();
};

DigitalOutput::DigitalOutput(uint8_t pin, bool active) {
  DigitalOutput(new DigitalPin(pin), active);
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