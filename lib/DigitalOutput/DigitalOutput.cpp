#include "DigitalOutput.h"
#include "Arduino.h"
#include "DigitalPin.h"

DigitalOutput::DigitalOutput(Pin* pin, bool active)
  : pin(pin), active(active) {
  pin->doPinMode(OUTPUT);
};

DigitalOutput::DigitalOutput(uint8_t pin, bool active) : active(active) {
  this->pin = new DigitalPin(pin);
  this->pin->doPinMode(OUTPUT);
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
