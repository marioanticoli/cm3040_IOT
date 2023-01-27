#include <map>
#include <tuple>
#include "Arduino.h"
#include "WebServer.h"
#include "WifiCredentials.h"
#include "Menu.h"
#include "DigitalPin.h"
#include "AnalogPin.h"
#include "DHTWrapper.h"
#include "LCDWrapper.h"
#include "IRWrapper.h"
#include "AnalogReader.h"
#include "NCRelayController.h"
#include "DigitalOutput.h"

#define DISPLAY_COLS 16
#define DISPLAY_ROWS 2
#define I2C_ADDRESS 0x27
// D1 SCL
// D2 SDA
// D3 FREE
#define WATER_PUMP_PIN D4
#define IR_PIN D5
#define DHT_PIN D6
#define MUX_PIN D7  // Using 1 pin instead of the canonical 3 allows me to control two inputs on the multiplexer, remaining PINs are set to 0 (GND)
#define LED_PIN D8
#define SOIL_SENSOR_PIN A0
#define PHOTO_PIN A0

#define DRY_VALUE 740
#define WET_VALUE 288
#define DARK_VALUE 1
#define LIGHT_VALUE 1024

#define LCD_PERIOD_MS 1000

uint now;
// LCD last updated time
uint lcdLastUpdate;

// Declare pointer to objects in global scope
WebServer* ws;
DHTWrapper* dht;
LCDWrapper* lcd;
AnalogReader* soilSensor;
AnalogReader* photo;
IRWrapper* ir;
NCRelayController* pump;
DigitalOutput* mux;
DigitalOutput* led;
Menu* menu;

// Input for the IR receiver
uint32_t command;
// Switch if to enter settings
bool fn;
// Switch if menu or sensor data;
bool showMenu;

void setup() {
  Serial.setDebugOutput(true);
  Serial.begin(9600);

  menu = new Menu();

  // // Initialise sensors, relays and outputs
  lcd = new LCDWrapper(I2C_ADDRESS, DISPLAY_COLS, DISPLAY_ROWS);
  lcd->display(0, 0, "Starting...");
  pump = new NCRelayController(WATER_PUMP_PIN);
  dht = new DHTWrapper(DHT_PIN);
  ir = new IRWrapper(IR_PIN);
  soilSensor = new AnalogReader(SOIL_SENSOR_PIN, WET_VALUE, DRY_VALUE, true);
  photo = new AnalogReader(PHOTO_PIN, DARK_VALUE, LIGHT_VALUE, false);
  mux = new DigitalOutput(MUX_PIN);
  led = new DigitalOutput(LED_PIN);

  initWebServer();

  lcdLastUpdate = millis() / 1000;
  fn = false;
  showMenu = false;
}

void loop() {
  now = millis();

  // Read DHT11
  dht->update();
  long soilHum, light;
  // Read analog sensor and switch the multiplexer to allow reading the other sensor
  soilHum = soilSensor->get_perc_value();
  mux->toggle();
  light = photo->get_perc_value();
  mux->toggle();

  // Listen to incoming requests to the webserver
  ws->listen();

  // Check if IR received a command and pass it to the Menu instance
  // POWER turns ON/OFF lcd
  // EQ toggles the menu
  // FUNC_STOP can be used to duplicate commands
  command = ir->getInput();
  if (command && command == IRWrapper::key::POWER) {
    lcd->toggle();
  } else if (command && command == IRWrapper::key::EQ) {
    lcd->clear();
    showMenu = !showMenu;
    fn = false;
    command = 0;
  } else if (command && showMenu && command == IRWrapper::key::FUNC_STOP) {
    fn = !fn;
    command = 0;
  }

  if (command != 0 && showMenu) {
    menuAction(menu->getAction((IRWrapper::key)command, fn));
    command = 0;
  }

  if (now - lcdLastUpdate >= LCD_PERIOD_MS) {
    if (showMenu) {
      lcd->display(0, 0, menu->display());
      lcd->clear(1);
    } else {
      showSensorData(soilHum, light);
    }
    lcdLastUpdate = now;
  }
}

void menuAction(Action action) {
  switch (action) {
    case Action::NEXT:
      menu->getNext();
      break;
    case Action::TOGGLE_LCD:
      lcd->toggle();
      break;
    case Action::TOGGLE_LED:
      led->toggle();
      break;
    case Action::TOGGLE_PUMP:
      pump->toggle();
      break;
  }
}

void showSensorData(long humidity, long light) {
  lcd->display(0, 0, "Light: " + String(light) + "%");
  lcd->display(1, 0, "Soil: " + String(humidity) + "%");
}

/*
*******************
WebServer block
*******************
*/

void initWebServer() {
  String openHTML = "<!DOCTYPE html><html><head><meta http-equiv=\"refresh\" content=\"2\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"></head><body><nav><ul><li><a href=\"/\">Environment readings</a></li><li><a href=\"/lights\">Control lights</a></li><li><a href=\"/pump\">Control pump</a></li></ul></nav><h1>Plant Care Dashboard</h1>";
  String closeHTML = "</body></html>";
  ws = new WebServer(openHTML, closeHTML);
  // Create routes
  std::map<String, std::tuple<String, int, String (*)(String), String>> r = {
    { "", std::make_tuple("GET", 200, &status, "") },
    { "/lights", std::make_tuple("GET", 200, &lightsControl, "") },
    { "/set_lights", std::make_tuple("POST", 200, &setLights, "status") },
    { "/pump", std::make_tuple("GET", 200, &pumpControl, "") },
    { "/set_pump", std::make_tuple("POST", 200, &setPump, "status") }
  };

  ws->setRoutes(r);

  ws->connect(SSID, PASSWORD);
  while (ws->getStatus() != "Connected") {
    Serial.println(ws->getStatus());
    delay(500);
  }
  Serial.println(ws->getStatus() + " with IP " + ws->getIPAddress().toString().c_str());
  if (ws->start()) {
    Serial.println("Started webserver");
  } else {
    Serial.println("Couldn't start the webserver.");
  }
}

// Callbacks for handling routes
String status(String _arg) {
  String pumpStatus = pump->isActive() ? "ON" : "OFF";
  String lightStatus = led->isActive() ? "ON" : "OFF";
  String sensors = "<h2>Environment readings</h2><p>Temperature: " + String(dht->getTemperature()) + "&deg;C</p><p>Humidity: " + String(dht->getHumidity()) + "%</p><p>Luminosity: " + String(photo->get_perc_value()) + "%</p><p>Soil humidity: " + String(soilSensor->get_perc_value()) + "%</p>";
  String actuators = "<h2>Actuators status</h2><p>Water pump: " + pumpStatus + "</p><p>Light: " + lightStatus + "</p>";
  return sensors + "<hr />" + actuators;
}

String lightsControl(String _arg) {
  return setStr(led->isActive(), "/set_lights", "lights");
}

String pumpControl(String _arg) {
  return setStr(pump->isActive(), "/set_pump", "pump");
}

String setStr(bool status, String endpoint, String output) {
  String val = status ? "OFF" : "ON";
  return "<form action=\"" + endpoint + "\"><p>Set the status of the " + output + ":</p><input type=\"hidden\" name=\"status\" value=\"" + val + "\"><input type=\"submit\" value=\"Turn " + val + "\"></form>";
}

String setLights(String arg) {
  if (arg == "ON") {
    led->on();
  } else {
    led->off();
  }
  return statusStr(led->isActive(), "Lights");
}

String setPump(String arg) {
  if (arg == "ON") {
    pump->on();
  } else {
    pump->off();
  }
  return statusStr(pump->isActive(), "Pump");
}

String statusStr(bool status, String output) {
  return String(output + " is currently " + status ? "ON" : "OFF");
}
