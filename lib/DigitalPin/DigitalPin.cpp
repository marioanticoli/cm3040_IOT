#include "Arduino.h"
#include "DigitalPin.h"

DigitalPin::DigitalPin(uint8_t pin) : Pin(pin) {}

void DigitalPin::doPinMode(uint8_t val) {
  pinMode(pin, val);
}

long DigitalPin::doRead() {
  return digitalRead(pin);
}

void DigitalPin::doWrite(uint8_t val) {
  digitalWrite(pin, val);
}
