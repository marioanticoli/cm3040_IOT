#include "AnalogReader.h"
#include "Arduino.h"
#include "AnalogPin.h"

AnalogReader::AnalogReader(Pin* pin, uint32_t min, uint32_t max)
  : pin(pin), min(min), max(max) {
    // TODO: is it necessary?
  pin->doPinMode(INPUT);
};

AnalogReader::AnalogReader(uint8_t pin, uint32_t min, uint32_t max) {
  AnalogReader(new AnalogPin(pin), min, max);
};

long AnalogReader::get_perc_value() {
  int value = pin->doRead();
  long perc_value = 100 - map(value, min, max, 0, 100);
  return perc_value;
}
