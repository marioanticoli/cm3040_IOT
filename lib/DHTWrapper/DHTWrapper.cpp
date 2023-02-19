#include "Arduino.h"
#include <DHT_U.h>
#include "DHTWrapper.h"

DHTWrapper::DHTWrapper(uint8_t pin, uint8_t type)
  : dht(DHT(pin, type)) {
  pinMode(pin, INPUT);
  dht.begin();
}

void DHTWrapper::update() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
}

float DHTWrapper::getTemperature() {
  return temperature;
}

float DHTWrapper::getHumidity() {
  return humidity;
}

