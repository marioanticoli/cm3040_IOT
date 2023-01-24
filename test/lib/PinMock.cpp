#include "Arduino.h"
#include "PinMock.h"

PinMock::PinMock(uint8_t pin) : Pin(pin) {}

void PinMock::doPinMode(uint8_t val) {}

long PinMock::doRead() {
    return value;
}

void PinMock::doWrite(uint8_t val) {}

void PinMock::setValue(long val) {
    value = val;
}