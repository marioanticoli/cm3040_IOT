#ifndef DHTWrapper_h
#define DHTWrapper_h
#pragma once
#include <DHT.h>

// Wrapper class for DHT11/22

class DHTWrapper {
private:
  float temperature;
  float humidity;
  DHT dht;

public:
  // Initialise a DHT11/22 sensor to a pin, set type of sensor (defaults to DHT11)
  DHTWrapper(uint8_t, uint8_t = DHT11);
  // Updates the temperature and humidity from the sensor (run before reading temperature or humidity)
  void update();
  // Returns the temperature
  float getTemperature();
  // Returns the humidity
  float getHumidity();
  // Returns a formatted string with temperature and humidity
  String toString();
};

#endif
