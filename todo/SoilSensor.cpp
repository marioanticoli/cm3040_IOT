#include "SoilSensor.h"
#include <iostream>
#include <string>

SoilSensor::SoilSensor(int pin): pin(pin) {};

int SoilSensor::get_humidity() {
  return 0;
}

void SoilSensor::print() {
  std::string hum = std::to_string(get_humidity());
  std::cout << "Soil Humidity: " << hum << std::endl;
}

