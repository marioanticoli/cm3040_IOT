#include "Arduino.h"
#include "DHTWrapper.h"

DHTWrapper::DHTWrapper(uint8_t pin) : dht(DHT(pin, DHT11)) {
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

String DHTWrapper::toString() {
  return "Temp.: " + String(temperature, 2) + " Hum.: " + String(humidity, 2);
}
