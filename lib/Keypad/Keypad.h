#ifndef Keypad_h
#define Keypad_h
#include "Arduino.h" 
#include <string>

class Keypad {
public:
  Keypad(int pin);
  std::string get_input();
private:
  int pin;
};
#endif
