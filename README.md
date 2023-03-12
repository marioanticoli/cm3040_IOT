# Plant care system - CM3040

- `plant_care.ino` is the main Arduino file
- `lib` contains custom classes to simplify working with sensors, actuators, etc. Each library contains specific tests (when appropriate).

## Important notes

**It is necessary to create a header file `WifiCredentials.h`**

It should containing the following definitions

```
#define SSID "NETWORK_NAME"
#define PASSWORD "NETWORK_PASSWORD"
```

**It is also necessary to import the libraries contained in `./lib`.**

You can do so by copying (or linking) them to your `libraries` folder of your Arduino sketchbook directory.

## Component list

- 1 x ESP8266 ESP-12F
- 1 x micro-usb cable
- 1 x I2C LCD 1602
- 1 x AX-1838HS IR receiver
- 1 x IR remote
- 1 x 1-channel 5V relay 
- 1 x submersible water pump 3-5V
- 1 x high power led 3V 1W red
- 2 x high power led 3V 1W blue
- 1 x 9V battery + snap-on connector
- 1 x TIP122 transistor
- 1 x DHT11 temperature and humidity sensor
- 1 x 74HC4051 8-channel analog multiplexer
- 1 x 3mm CdS photoresistor
- 1 x 1KOhm resistor
- 1 x capacitative soil mosture sensor
- 4 x crocodile clips
- jumper wires