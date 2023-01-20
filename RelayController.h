#ifndef RelayController_h
#define RelayController_h
#include "Arduino.h"

class RelayController {
private:
  uint8_t pin;
  bool active;
  bool mode;

  enum mode {
    NO = true,
    NC = false
  };

  void write();

public:
  RelayController(uint8_t, bool=true);
  void on();
  void off();
  void toggle();
};
#endif
