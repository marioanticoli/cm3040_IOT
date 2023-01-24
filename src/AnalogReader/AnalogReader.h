#ifndef AnalogReader_h
#define AnalogReader_h
#include "Arduino.h"

// Class to manage analog inputs

class AnalogReader {
private:
  uint8_t pin;
  uint min;
  uint max;

public:
  // Initialise a analog input to a pin, store range for mapping
  AnalogReader(uint8_t, uint, uint);
  // Return the read from the analog input mapped to the given range
  long get_perc_value();
};

#endif
