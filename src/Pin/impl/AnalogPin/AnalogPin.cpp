#include "Arduino.h"
#include "Pin.h"
#include "AnalogPin.h"

AnalogPin::AnalogPin(uint8_t pin) : Pin(pin) {}

void AnalogPin::doPinMode(uint8_t val) {}

void AnalogPin::doRead() {
    analogRead(pin, val);
}

void AnalogPin::doWrite(uint8_t val) {
    analogWrite(pin, val);
}