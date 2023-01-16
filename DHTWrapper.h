#include <DHT.h>

#ifndef DHTWrapper_h
#define DHTWrapper_h

class DHTWrapper {
private:
  float temperature;
  float humidity;
  DHT dht;
  String toString();

public:
  DHTWrapper(uint8_t, uint8_t=DHT11);
  String update();
  float getTemperature();
  float getHumidity();
};

#endif
