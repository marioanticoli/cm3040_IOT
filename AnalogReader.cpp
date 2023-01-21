#include "AnalogReader.h"

AnalogReader::AnalogReader(uint8_t pin, uint min, uint max)
  : pin(pin), min(min), max(max) {
  pinMode(pin, INPUT);
};

long AnalogReader::get_perc_value() {
  int value = analogRead(pin);
  long perc_value = 100 - map(value, min, max, 0, 100);
  return perc_value;
}
