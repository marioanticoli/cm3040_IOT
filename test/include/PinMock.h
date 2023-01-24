#ifndef PinMock_h
#define PinMock_h
#pragma once
#include "Pin.h"

// Implementation of PinMock class

class PinMock: public Pin {
private:
  long value;

public:
  PinMock(uint8_t);
  void doPinMode(uint8_t);
  long doRead();
  void doWrite(uint8_t);
  void setValue(long);
};

#endif