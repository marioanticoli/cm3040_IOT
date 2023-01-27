#ifndef DigitalPin_h
#define DigitalPin_h
#pragma once
#include "Pin.h"

// Implementation of Pin class for digital pins

class DigitalPin: public Pin {
public:
  DigitalPin(uint8_t);
  void doPinMode(uint8_t);
  long doRead();
  void doWrite(uint8_t);
};

#endif
