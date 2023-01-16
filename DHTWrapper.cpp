#include "Arduino.h"
#include <DHT_U.h>
#include "DHTWrapper.h"

DHTWrapper::DHTWrapper(uint8_t pin, uint8_t type)
  : dht(DHT(pin, type)) {
  pinMode(pin, INPUT);  
  dht.begin();
}

String DHTWrapper::update() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  return toString();
}

float DHTWrapper::getTemperature() {
  return temperature;
}

float DHTWrapper::getHumidity() {
  return humidity;
}

String DHTWrapper::toString() {
  return "Temp.: " + String(temperature, 2) + "C - Hum.: " + String(humidity, 2) + "%";
}
