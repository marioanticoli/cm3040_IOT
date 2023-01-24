#ifndef AnalogReader_h
#define AnalogReader_h
#pragma once
#include "Pin.h"
#include <stdint.h>

// Class to manage analog inputs

class AnalogReader {
private:
  Pin* pin;
  uint32_t min;
  uint32_t max;

public:
  // Initialise a analog input, store range for mapping
  AnalogReader(Pin*, uint32_t, uint32_t);
  AnalogReader(uint8_t, uint32_t, uint32_t);
  // Return the read from the analog input mapped to the given range
  long get_perc_value();
};

#endif
