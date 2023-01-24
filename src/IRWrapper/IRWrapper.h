#ifndef IRWrapper_h
#define IRWrapper_h
#include <IRrecv.h>

#define DEFAULT_DEBOUNCE 200
// Wrapper class to IR receiver

class IRWrapper {
private:
  IRrecv receiver;
  uint16_t debounce;

public:
  // Initialise an IR receiver to a pin and a debounce in ms (defaults to DEFAULT_DEBOUNCE)
  IRWrapper(uint8_t, uint16_t = DEFAULT_DEBOUNCE);
  // Returns the code received
  uint32_t getInput();

  // Mapping of received values
  enum key {
    POWER = 0xFFA25D,
    FUNC_STOP = 0xFFE21D,
    VOL_UP = 0xFF629D,
    FAST_BACK = 0xFF22DD,
    PAUSE = 0xFF02FD,
    FAST_FORWARD = 0xFFC23D,
    DOWN = 0xFFE01F,
    VOL_DOWN = 0xFFA857,
    UP = 0xFF906F,
    EQ = 0xFF9867,
    ST_REPT = 0xFFB04F,
    NR_0 = 0xFF6897,
    NR_1 = 0xFF30CF,
    NR_2 = 0xFF18E7,
    NR_3 = 0xFF7A85,
    NR_4 = 0xFF10EF,
    NR_5 = 0xFF38C7,
    NR_6 = 0xFF5AA5,
    NR_7 = 0xFF42BD,
    NR_8 = 0xFF4AB5,
    NR_9 = 0xFF52AD,
    REPEAT = 0xFFFFFFFF
  };
};

#endif
