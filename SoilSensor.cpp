#include "SoilSensor.h"

SoilSensor::SoilSensor(uint8_t pin): pin(pin) {
    pinMode(pin, INPUT);
};

static const int DRY_VALUE = 740;
static const int WET_VALUE = 288;

long SoilSensor::get_humidity() {
  int value = analogRead(pin);
  long perc_value = 100 - map(value, WET_VALUE, DRY_VALUE, 0, 100);
  return perc_value;
}
