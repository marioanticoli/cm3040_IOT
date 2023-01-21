#include "DigitalOutput.h"

DigitalOutput::DigitalOutput(uint8_t pin, bool active)
  : pin(pin), active(active) {
  pinMode(pin, OUTPUT);
  toggle();
};

// Change the state of the digital output; LOW -> HIGH or HIGH -> LOW
void DigitalOutput::toggle() {
  digitalWrite(pin, active ? LOW : HIGH);
  active = !active;
}

bool DigitalOutput::isActive() {
  return active;
}