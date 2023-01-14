#ifndef LCDWrapper_h
#define LCDWrapper_h
#include "Arduino.h"
#include <LiquidCrystal_I2C.h>

class LCDWrapper {
  private:
    uint8_t cols;
    uint8_t rows;
    LiquidCrystal_I2C lcd;

  public:
    LCDWrapper(uint8_t, uint8_t, uint8_t);
    bool display(uint8_t, uint8_t, String);
};

#endif
