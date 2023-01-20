#include "WebServer.h"
#include "WifiCredentials.h"
#include <map>
#include <tuple>
#include "DHTWrapper.h"
#include "LCDWrapper.h"
#include "AnalogReader.h"
#include "IRWrapper.h"
#include "RelayController.h"

#define DISPLAY_COLS 16
#define DISPLAY_ROWS 2
#define LCD_AUTOSCROLL false
#define I2C_ADDRESS 0x27
// D1 SCL
// D2 SDA
// D3 FREE
#define WATER_PUMP_PIN D4
#define IR_PIN D5
#define DHT_PIN D6
#define LED_PIN D7
// D8 FREE
#define SOIL_SENSOR_PIN A0
// #define PHOTO_SENSOR_PIN A0

#define DRY_VALUE 740
#define WET_VALUE 288

#define LCD_PERIOD_MS 1000

uint now;
uint lcdLastUpdate;

WebServer* ws;
DHTWrapper* dht;
LCDWrapper* lcd;
AnalogReader* soilSensor;
IRWrapper* ir;
RelayController* pump;

uint32_t command;

void setup() {
  Serial.setDebugOutput(true);
  Serial.begin(9600);

  pump = new RelayController(WATER_PUMP_PIN);
  dht = new DHTWrapper(DHT_PIN);
  lcd = new LCDWrapper(I2C_ADDRESS, DISPLAY_COLS, DISPLAY_ROWS, LCD_AUTOSCROLL);
  ir = new IRWrapper(IR_PIN);
  soilSensor = new AnalogReader(SOIL_SENSOR_PIN, WET_VALUE, DRY_VALUE);
  initWebServer();

  lcdLastUpdate = millis() / 1000;
}

void loop() {
  now = millis();

  ws->listen();
  if (uint32_t res = ir->getInput()) {
    if (res == IRWrapper::Key::POWER) {
      lcd->toggle();
    }
  }

  long humidity = soilSensor->get_perc_value();
  if (humidity > 50) {
    pump->on();
  } else {
    pump->off();
  }

  // It will eventually overflow but it might just skip an update and restart from 0
  if (now - lcdLastUpdate >= LCD_PERIOD_MS) {
    lcd->display(0, 0, dht->update());
    lcd->display(1, 0, String("Soil: ") + String(humidity));
    lcdLastUpdate = now;
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
  std::map<String, std::tuple<String, int, String (*)()>> r = {
    { "", std::make_tuple("GET", 200, &home) },
    { "status", std::make_tuple("GET", 200, &status) },
    { "set_status", std::make_tuple("POST", 200, &setStatus) }
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
String home() {
  return "<h2>Welcome to homepage</h2>";
}

String status() {
  return "<h2>" + dht->update() + "</h2>";
}

String setStatus() {
  return "<h2>POST request</h2>";
}
