#ifndef AnalogReader_h
#define AnalogReader_h
#include "Arduino.h"

class AnalogReader {
private:
  uint8_t pin;
  uint min;
  uint max;

public:
  AnalogReader(uint8_t, uint, uint);
  long get_perc_value();
};
#endif
