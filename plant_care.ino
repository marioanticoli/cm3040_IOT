#include <map>
#include <tuple>
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
#include "index.h"

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
#define ANALOG_SENSOR_PERIOD_MS 2500

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
String line[2];
uint currPlantSetting;
bool bypassLED, bypassPump;

long soilHum, light;

void setup() {
  Serial.setDebugOutput(true);
  Serial.begin(9600);

  initWebServer();

  // Initialise sensors, relays and outputs
  lcd = new LCDWrapper(I2C_ADDRESS, DISPLAY_COLS, DISPLAY_ROWS);
  lcd->display(0, 0, "Starting...");
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

  soilHum = soilSensor->get_perc_value();
  mux->toggle();
  light = photo->get_perc_value();  
  mux->toggle();
}

void loop() {
  // Listen to incoming requests to the webserver
  ws->listen();

  now = millis();

  // Read DHT11
  dht->update();

  // Read one analog sensor every ANALOG_SENSOR_PERIOD_MS
  if(now % (ANALOG_SENSOR_PERIOD_MS * 2) == 0) {
    soilHum = soilSensor->get_perc_value();
    mux->toggle();
  } else if (now % ANALOG_SENSOR_PERIOD_MS == 0) {
    light = photo->get_perc_value();  
    mux->toggle();
  }

  // Check if values for humidity and light reach current target
  // better to pour water slowly
  if (now % PUMP_PERIOD_MS == 0 && soilHum < setting[currPlantSetting].getHumidity() && !bypassPump) {
    // turn on for 50ms not to flood the soil
    pump->on();
    delay(50);
    pump->off();
  }

  if(!bypassLED) {
    if (light < setting[currPlantSetting].getLuminosity()) {
      led->on();
    } else {
      led->off();
    }    
  }

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
  if (now % LCD_PERIOD_MS == 0) {
    if (!menuActive) {
      line[0] = "Light: " + String(light) + "%";
      line[1] = "Soil: " + String(soilHum) + "%";
    }

    lcd->display(0, 0, line[0]);
    lcd->display(1, 0, line[1]);
  }
}



/*
*******************
WebServer block
*******************
*/

void initWebServer() {
  ws = new WebServer();
  // Create routes
  String params[1] = { "Status" };
  String params_plant[3] = { "plant", "humidity", "luminosity" };
  // map<endpoint, tuple<method, status, callback, response_type>>
  std::map<String, std::tuple<String, int, String (*)(String), String>> r = {
    { "", std::make_tuple("GET", 200, &status, "text/html") },
    { "temperature", std::make_tuple("GET", 200, &getTemperature, "text/plain") },
    { "humidity", std::make_tuple("GET", 200, &getHumidity, "text/plain") },
    { "luminosity", std::make_tuple("GET", 200, &getLuminosity, "text/plain") },
    { "soil", std::make_tuple("GET", 200, &getSoilHum, "text/plain") },
    { "pump-status", std::make_tuple("GET", 200, &getPumpStatus, "text/plain") },
    { "light-status", std::make_tuple("GET", 200, &getLEDStatus, "text/plain") },
    { "current-setting", std::make_tuple("GET", 200, &getCurrentSetting, "text/json") },
    { "toggle-pump", std::make_tuple("POST", 200, &togglePumpStatus, "text/plain") },
    { "toggle-led", std::make_tuple("POST", 200, &toggleLEDStatus, "text/plain") },
  };

  ws->setRoutes(r);

  ws->connect(SSID, PASSWORD);
  while (ws->getStatus() != "Connected") {
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

String status(String arg) {
  return INDEX_page;
}

String getTemperature(String arg) {
  return String(dht->getTemperature());
}

String getHumidity(String arg) {
  return String(dht->getHumidity());
}

String getLuminosity(String arg) {
  return String(light);
}

String getSoilHum(String arg) {
  return String(soilHum);
}

String getPumpStatus(String arg) {
  return String(pump->isActive() ? "ON" : "OFF");
}

String getLEDStatus(String arg) {
  return String(led->isActive() ? "ON" : "OFF");
}

String getCurrentSetting(String arg) {
  return "{\"i\": " + String(currPlantSetting) + ",\"h\": " + String(setting[currPlantSetting].getHumidity()) + ",\"l\": " + String(setting[currPlantSetting].getLuminosity()) + "}";
}

String togglePumpStatus(String arg) {
  bypassPump = true;
  pump->toggle();
  return getPumpStatus();
}

String toggleLEDStatus(String arg) {
  bypassLED = true;
  led->toggle();
  return getLEDStatus();
}

String setCurrentPlant(String arg) {

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
      line[0] = String("Toggle LED");
      line[1] = String(led->isActive() ? "ON -> OFF" : "OFF -> ON");
      break;
    case Action::TOGGLE_PUMP:
      line[0] = String("Toggle pump");
      line[1] = String(pump->isActive() ? "ON -> OFF" : "OFF -> ON");
      break;
    case Action::SET_PLANT:
      line[0] = String("Set plant");
      line[1] = String("'PLAY' + [1-3]");
      break;
    case Action::SET_HUMIDITY:
      line[0] = String("Plant ") + String(currPlantSetting + 1);
      line[1] = String("Hum. ") + String(setting[currPlantSetting].getHumidity()) + String("%");
      break;
    case Action::SET_LUMINOSITY:
      line[0] = String("Plant ") + String(currPlantSetting + 1);
      line[1] = String("Light ") + String(setting[currPlantSetting].getLuminosity()) + String("%");
      break;
    case Action::BACK:
      line[0] = String("Go to main menu");
      line[1] = String("");
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
