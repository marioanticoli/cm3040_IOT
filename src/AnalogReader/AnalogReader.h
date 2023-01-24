#ifndef AnalogReader_h
#define AnalogReader_h
#include "Pin.h"

// Class to manage analog inputs

class AnalogReader {
private:
  Pin* pin;
  uint min;
  uint max;

public:
  // Initialise a analog input to a Pin, store range for mapping
  AnalogReader(Pin*, uint, uint);
  // Return the read from the analog input mapped to the given range
  long get_perc_value();
};

#endif
