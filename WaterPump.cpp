#include "WaterPump.h"

// Work with 3 pin relay in NC
WaterPump::WaterPump(uint8_t pin)
  : pin(pin) {
  pinMode(pin, OUTPUT);
  off();
};

void WaterPump::on() {
  digitalWrite(pin, LOW);
};

void WaterPump::off() {
  digitalWrite(pin, HIGH);
};
