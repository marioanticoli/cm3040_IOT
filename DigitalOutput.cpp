#include "DigitalOutput.h"

DigitalOutput::DigitalOutput(uint8_t pin, bool active)
  : pin(pin), active(active) {
  pinMode(pin, OUTPUT);
  toggle();
};

void DigitalOutput::on() {
  if (!active) {
    digitalWrite(pin, HIGH);
    active = true;
  }
}

void DigitalOutput::off() {
  if (active) {
    digitalWrite(pin, LOW);
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