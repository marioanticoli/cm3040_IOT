#ifndef LCDWrapper_h
#define LCDWrapper_h
#include "Arduino.h"
#include <LiquidCrystal_I2C.h>

// Wrapper class for LCD

class LCDWrapper {
private:
  uint8_t cols;
  uint8_t rows;
  LiquidCrystal_I2C lcd;
  bool on;

public:
  // Initialise an LCD at an address with given rows and columns
  LCDWrapper(uint8_t, uint8_t, uint8_t);
  // Display at row, col a given message
  bool display(uint8_t, uint8_t, String);
  // Turn on and off the display
  void toggle();
  // Clear the display
  void clear();
};

#endif
