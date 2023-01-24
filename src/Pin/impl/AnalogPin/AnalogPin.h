#ifndef AnalogPin_h
#define AnalogPin_h
#pragma once
#include "Pin.h"

// Implementation of Pin class for analog pins

class AnalogPin: public Pin {
public:
  AnalogPin(uint8_t);
  void doPinMode(uint8_t);
  long doRead();
  void doWrite(uint8_t);
};

#endif