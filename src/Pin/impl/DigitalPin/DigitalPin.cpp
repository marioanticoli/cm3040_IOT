#include "Arduino.h"
#include "Pin.h"
#include "DigitalPin.h"

DigitalPin::DigitalPin(uint8_t pin) : Pin(pin) {}

void DigitalPin::doPinMode(uint8_t val) {
    pinMode(pin, val);
}

void DigitalPin::doRead() {
    digitalRead(pin, val);
}

void DigitalPin::doWrite(uint8_t val) {
    digitalWrite(pin, val);
}