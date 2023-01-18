#ifndef IRWrapper_h
#define IRWrapper_h

#include <IRrecv.h>

class IRWrapper {
private:
  IRrecv receiver;

public:
  IRWrapper(uint8_t);
  uint32_t getInput();

  enum Key {
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
