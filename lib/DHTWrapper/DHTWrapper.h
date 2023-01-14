#ifndef DHTWrapper_h
#define DHTWrapper_h
#include "Arduino.h"
#include <DHT.h>
#include <DHT_U.h>

class DHTWrapper {
  private:
    float temperature;
    float humidity;
    DHT dht;

  public:
    DHTWrapper(uint8_t pin);
    void update();
    float getTemperature();
    float getHumidity();
    String toString();
};

#endif
