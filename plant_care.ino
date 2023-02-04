#include <map>
#include <tuple>
#include <string>
#include "Arduino.h"
#include "WebServer.h"
#include "WifiCredentials.h"
#include "DigitalPin.h"
#include "AnalogPin.h"
#include "DHTWrapper.h"
#include "LCDWrapper.h"
#include "IRWrapper.h"
#include "AnalogReader.h"
#include "NCRelayController.h"
#include "DigitalOutput.h"
#include "Menu.h"
#include "PlantSetting.h"

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

#define DRY_VALUE 770
#define WET_VALUE 288
#define DARK_VALUE 1
#define LIGHT_VALUE 1024

#define LCD_PERIOD_MS 500
#define PUMP_PERIOD_MS 10000

#define PLANT_SIZE 3

enum class Action {
  TOGGLE_LED,
  TOGGLE_PUMP,
  SET_PLANT,
  SET_HUMIDITY,
  SET_LUMINOSITY,
  BACK,
};

uint now;
// LCD last updated time
uint lcdLastUpdate;
// Pump last updated time
uint pumpLastUpdate;
// Input for the IR receiver
uint32_t command;

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
Menu<Action>* mainMenu;
Menu<Action>* subMenu;
Menu<Action>* currMenu;

PlantSetting setting[PLANT_SIZE];
bool menuActive;
std::string line[2];
uint currPlantSetting;
bool bypassLED, bypassPump;

void setup() {
  Serial.setDebugOutput(true);
  Serial.begin(9600);

  // Initialise sensors, relays and outputs
  lcd = new LCDWrapper(I2C_ADDRESS, DISPLAY_COLS, DISPLAY_ROWS);
  lcd->display(0, 0, (std::string *)"Starting...");
  pump = new NCRelayController(WATER_PUMP_PIN);
  dht = new DHTWrapper(DHT_PIN);
  ir = new IRWrapper(IR_PIN);
  soilSensor = new AnalogReader(SOIL_SENSOR_PIN, WET_VALUE, DRY_VALUE, true);
  photo = new AnalogReader(PHOTO_PIN, DARK_VALUE, LIGHT_VALUE, false);
  mux = new DigitalOutput(MUX_PIN);
  led = new DigitalOutput(LED_PIN);

  // Initialise menu
  Action arr1[3] = { Action::TOGGLE_LED, Action::TOGGLE_PUMP, Action::SET_PLANT };
  mainMenu = new Menu<Action>(arr1, 3);
  Action arr2[3] = { Action::SET_HUMIDITY, Action::SET_LUMINOSITY, Action::BACK };
  subMenu = new Menu<Action>(arr2, 3);
  currMenu = mainMenu;
  menuActive = false;

  initWebServer();

  lcdLastUpdate = millis() / 1000;
  pumpLastUpdate = lcdLastUpdate;
}

size_t getTotalAvailableMemory() {
  return ESP.getFreeHeap();
}

size_t getLargestAvailableBlock() {
  return ESP.getMaxFreeBlockSize();
}

float getFragmentation() {
  return 100 - getLargestAvailableBlock() * 100.0 / getTotalAvailableMemory();
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

  // Check if values for humidity and light reach current target
  // better to pour water slowly
  if (now - pumpLastUpdate >= PUMP_PERIOD_MS && soilHum < setting[currPlantSetting].getHumidity() && !bypassPump) {
    // turn on for 100ms not to flood the soil
    pump->on();
    delay(100);
    pump->off();
    pumpLastUpdate = now;
  }

  if (light < setting[currPlantSetting].getLuminosity() && !bypassLED) {
    led->on();
  } else {
    led->off();
  }

  // Listen to incoming requests to the webserver
  ws->listen();

  // Check if IR received a command and react if valid
  // POWER turns ON/OFF lcd
  // FUNC_STOP toggles the menu
  // EQ reset bypass to allow automatic control of pump and LED
  command = ir->getInput();
  if (command && command == IRWrapper::key::POWER) {
    lcd->toggle();
  } else if (command && command == IRWrapper::key::FUNC_STOP) {
    lcd->clear();
    toggleMenu();
  } else if (command && command == IRWrapper::key::EQ) {
    bypassLED = false;
    bypassPump = false;
  } else if (command && menuActive) {
    menuAction(command);
  }
  command = 0;

  // update every LCD_PERIOD_MS ms, not blocking unlike delay()
  if (now - lcdLastUpdate >= LCD_PERIOD_MS) {
    if (!menuActive) {
      line[0] = "Light: " + std::to_string(light) + "%";
      line[1] = "Soil: " + std::to_string(soilHum) + "%";
    }
    lcd->display(0, 0, &line[0]);
    lcd->display(1, 0, &line[1]);

    lcdLastUpdate = now;
  }
}



/*
*******************
WebServer block
*******************
*/

void initWebServer() {
  std::string openHTML = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"></head><body><nav><ul><li><a href=\"/\">Environment readings</a></li><li><a href=\"/lights\">Control lights</a></li><li><a href=\"/pump\">Control pump</a></li></ul></nav><h1>Plant Care Dashboard</h1>";
  std::string closeHTML = "</body></html>";
  ws = new WebServer(openHTML, closeHTML);
  // Create routes
  std::string params[1] = { "Status" };
  std::string params_plant[3] = { "plant", "humidity", "luminosity" };
  // map<endpoint, tuple<method, status, callback, params, params_size>>
  std::map<std::string, std::tuple<std::string, int, std::string (*)(std::string*, uint8_t), std::string*, uint8_t>> r = {
    { "", std::make_tuple("GET", 200, &status, params, 0) },
    { "lights", std::make_tuple("GET", 200, &lightsControl, params, 0) },
    { "pump", std::make_tuple("GET", 200, &pumpControl, params, 0) },
    { "set_lights", std::make_tuple("POST", 200, &setLights, params, 1) },
    { "set_pump", std::make_tuple("POST", 200, &setPump, params, 1) },
    // { "set_plant", std::make_tuple("POST", 200, &setPlant, params_plant, 3) },
  };

  ws->setRoutes(r);

  ws->connect(SSID, PASSWORD);
  while (ws->getStatus() != "Connected") {
    Serial.println(ws->getStatus().c_str());
    delay(500);
  }
  Serial.print(ws->getStatus().c_str());
  Serial.println(ws->getIPAddress().toString().c_str());
  if (ws->start()) {
    Serial.println("Started webserver");
  } else {
    Serial.println("Couldn't start the webserver.");
  }
}

// Callbacks for handling routes
std::string status(std::string* _arg, uint8_t _size) {
  std::string pumpStatus = pump->isActive() ? "ON" : "OFF";
  std::string ledStatus = led->isActive() ? "ON" : "OFF";
  std::string sensors = "<h2>Environment readings</h2><p>Temperature: " + std::to_string(dht->getTemperature()) + "&deg;C</p><p>Humidity: " + std::to_string(dht->getHumidity()) + "%</p><p>Luminosity: " + std::to_string(photo->get_perc_value()) + "%</p><p>Soil humidity: " + std::to_string(soilSensor->get_perc_value()) + "%</p>";
  std::string actuators = "<h2>Actuators status</h2><p>Water pump: " + pumpStatus + "</p>" + "<p>Light: " + ledStatus + "</p>";
  std::string settings = "<h2>Plant settings</h2><p>Selected plant: " + std::to_string(currPlantSetting + 1) + "</p>";

  return sensors + "<hr />" + actuators + "<hr />" + settings;
}

std::string setStr(bool status, std::string endpoint, std::string output) {
  std::string val = status ? "OFF" : "ON";
  return "<form action=\"" + endpoint + "\" method=\"POST\"><p>Set the status of the " + output + ":</p><input type=\"hidden\" name=\"status\" value=\"" + val + "\"><input type=\"submit\" value=\"Turn " + val + "\"></form>";
}

std::string setLights(std::string* arg, uint8_t size) {
  if (size > 0) {
    bypassLED = true;
    Serial.println(arg[0].c_str());
    if (arg[0] == "ON") {
      led->on();
    } else {
      led->off();
    }
  }
  return statusStr(led->isActive(), "Lights");
}

std::string setPump(std::string* arg, uint8_t size) {
  if (size > 0) {
    bypassPump = true;
    if (arg[0] == "ON") {
      pump->on();
    } else {
      pump->off();
    }
  }
  return statusStr(pump->isActive(), "Pump");
}

std::string statusStr(bool status, std::string output) {
  return output + " is now " + (status ? "ON" : "OFF");
}

std::string lightsControl(std::string* _arg, uint8_t _size) {
  return setStr(led->isActive(), "/set_lights", "lights");
}

std::string pumpControl(std::string* _arg, uint8_t _size) {
  return setStr(pump->isActive(), "/set_pump", "pump");
}

std::string setPlant(std::string* arg, uint8_t size) {
  // if(size == 3) {
  //   uint8_t ind = std::string(arg[0]).toInt();
  //   uint8_t h = std::string(arg[1]).toInt();
  //   uint8_t l = std::string(arg[2]).toInt();
  //   setting[ind].setHumidity(h);
  //   setting[ind].setLuminosity(l);
  // }
  return "";
}

/*
*******************
Menu block
*******************
*/

void toggleMenu() {
  menuActive = !menuActive;
  currMenu = mainMenu;
  mainMenu->reset();
  subMenu->reset();
  setMenuDisplay();
}

void setMenuDisplay() {
  switch (currMenu->getItem()) {
    case Action::TOGGLE_LED:
      line[0] = "Toggle LED";
      line[1] = led->isActive() ? "ON -> OFF" : "OFF -> ON";
      break;
    case Action::TOGGLE_PUMP:
      line[0] = "Toggle pump";
      line[1] = pump->isActive() ? "ON -> OFF" : "OFF -> ON";
      break;
    case Action::SET_PLANT:
      line[0] = "Set plant";
      line[1] = "'PLAY' + [1-3]";
      break;
    case Action::SET_HUMIDITY:
      line[0] = "Plant " + std::to_string(currPlantSetting + 1);
      line[1] = "Hum. " + std::to_string(setting[currPlantSetting].getHumidity()) + "%";
      break;
    case Action::SET_LUMINOSITY:
      line[0] = "Plant " + std::to_string(currPlantSetting + 1);
      line[1] = "Light " + std::to_string(setting[currPlantSetting].getLuminosity()) + "%";
      break;
    case Action::BACK:
      line[0] = "Go to main menu";
      line[1] = "";
      break;
  }
}

void execMenuHandler() {
  switch (currMenu->getItem()) {
    case Action::TOGGLE_LED:
      led->toggle();
      bypassLED = true;
      break;
    case Action::TOGGLE_PUMP:
      pump->toggle();
      bypassPump = true;
      break;
    case Action::SET_PLANT:
      currMenu = subMenu;
      break;
    case Action::BACK:
      currMenu->reset();
      currMenu = mainMenu;
      break;
  }
}

void adjustValue(int8_t value) {
  if (currMenu->getItem() == Action::SET_LUMINOSITY) {
    setting[currPlantSetting].incLuminosity(value);
  } else if (currMenu->getItem() == Action::SET_HUMIDITY) {
    setting[currPlantSetting].incHumidity(value);
  }
}

void menuAction(uint32_t command) {
  switch (command) {
    case IRWrapper::key::FAST_FORWARD:
      currMenu->next();
      break;
    case IRWrapper::key::PLAY_PAUSE:
      execMenuHandler();
      break;
    case IRWrapper::key::NR_1:
      if (currMenu == subMenu) currPlantSetting = 0;
      break;
    case IRWrapper::key::NR_2:
      if (currMenu == subMenu) currPlantSetting = 1;
      break;
    case IRWrapper::key::NR_3:
      if (currMenu == subMenu) currPlantSetting = 2;
      break;
    case IRWrapper::key::DOWN:
      if (currMenu == subMenu) adjustValue(-5);
      break;
    case IRWrapper::key::UP:
      if (currMenu == subMenu) adjustValue(5);
      break;
  }
  setMenuDisplay();
}
