#ifndef Pin_h
#define Pin_h

// Abstract class for pins

class Pin {
protected:
  uint8_t pin;

public:
  Pin(uint8_t);
  virtual void doPinMode(uint8_t mode) ;
  virtual void doRead();
  virtual void doWrite(uint8_t val);
};

#endif