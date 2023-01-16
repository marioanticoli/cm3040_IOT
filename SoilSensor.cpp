#include "SoilSensor.h"

SoilSensor::SoilSensor(int pin): pin(pin) {};

static const int DRY_VALUE = 740;
static const int WET_VALUE = 288;

long SoilSensor::get_humidity() {
  int value = analogRead(pin);
  long perc_value = map(value, WET_VALUE, DRY_VALUE, 100, 0);
  return perc_value;
}
