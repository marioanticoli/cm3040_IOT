#ifndef Pin_h
#define Pin_h
#include <stdint.h>

// Abstract class for pins

class Pin {
protected:
  uint8_t pin;

public:
  Pin(uint8_t);
  virtual void doPinMode(uint8_t) = 0;
  virtual long doRead() = 0;
  virtual void doWrite(uint8_t) = 0;
};

#endif