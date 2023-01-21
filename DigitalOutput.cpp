#include "DigitalOutput.h"

DigitalOutput::DigitalOutput(uint8_t pin, bool state)
  : pin(pin), state(state) {
  pinMode(pin, OUTPUT);
  toggleState();
};

// Change the state of the digital output; LOW -> HIGH or HIGH -> LOW
void DigitalOutput::toggleState() {
  digitalWrite(pin, state ? LOW : HIGH);
  state = !state;
}