#include "AnalogReader.h"
#include "Arduino.h"
#include "AnalogPin.h"

AnalogReader::AnalogReader(Pin* pin, uint32_t min, uint32_t max, bool invert)
  : pin(pin), min(min), max(max), invert(invert) {
  pin->doPinMode(INPUT);
};

AnalogReader::AnalogReader(uint8_t pin, uint32_t min, uint32_t max, bool invert)
  : min(min), max(max), invert(invert) {
  this->pin = new AnalogPin(pin);
  this->pin->doPinMode(INPUT);
};

long AnalogReader::get_perc_value() {
  int value = pin->doRead();
  return invert ? map(value, max, min, 0, 100) : 100 - map(value, max, min, 0, 100);
}
