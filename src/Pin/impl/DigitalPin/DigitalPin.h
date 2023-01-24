#ifndef DigitalPin_h
#define DigitalPin_h

// Implementation of Pin class for digital pins

class DigitalPin: public Pin {
public:
  DigitalPin(uint8_t);
  void doPinMode(uint8_t);
  void doRead();
  void doWrite(uint8_t);
};

#endif