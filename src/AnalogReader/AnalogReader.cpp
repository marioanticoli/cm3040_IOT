#include "AnalogReader.h"

AnalogReader::AnalogReader(Pin* pin, uint min, uint max)
  : pin(pin), min(min), max(max) {
  pin->doPinMode();
};

long AnalogReader::get_perc_value() {
  int value = pin->doAnalogRead();
  long perc_value = 100 - map(value, min, max, 0, 100);
  return perc_value;
}
