#include "Arduino.h"
#include "AnalogPin.h"

AnalogPin::AnalogPin(uint8_t pin) : Pin(pin) {}

void AnalogPin::doPinMode(uint8_t val) {
    pinMode(pin, val);
}

long AnalogPin::doRead() {
    return analogRead(pin);
}

void AnalogPin::doWrite(uint8_t val) {
    analogWrite(pin, val);
}