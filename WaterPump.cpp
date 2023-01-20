#include "WaterPump.h"

// Work with 3 pin relay in NC
WaterPump::WaterPump(uint8_t pin)
  : pin(pin) {

  pinMode(pin, OUTPUT);
  active = false;
};

void WaterPump::on() {  
  if (!active) {
    digitalWrite(pin, LOW);
    active = true;
  }
};

void WaterPump::off() {
  if (active) {
    digitalWrite(pin, HIGH);
    active = false;
  }
};

void WaterPump::toggle() {
  if (active) {
    off();
  } else {
    on();
  }
};
