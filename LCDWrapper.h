#ifndef LCDWrapper_h
#define LCDWrapper_h
#include "Arduino.h"
#include <LiquidCrystal_I2C.h>

/*
Serial Clock (SCL) on pin D1
Serial Data (SDA) on pin D2
*/

class LCDWrapper {
private:
  uint8_t cols;
  uint8_t rows;
  LiquidCrystal_I2C lcd;

public:
  LCDWrapper(uint8_t, uint8_t, uint8_t, bool=false);
  bool display(uint8_t, uint8_t, String);
  void clear();
};

#endif
