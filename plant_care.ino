#include "WebServer.h"
#include "WifiCredentials.h"
#include <map>
#include <tuple>
#include "DHTWrapper.h"
#include "LCDWrapper.h"
#include "SoilSensor.h"
#include "IRWrapper.h"

#define IR_PIN D5
#define DHT_PIN D6
#define SOIL_SENSOR_PIN A0
#define I2C_ADDRESS 0x27
#define DISPLAY_COLS 16
#define DISPLAY_ROWS 2
#define LCD_AUTOSCROLL false
#define LCD_PERIOD_SEC 1

uint now;
uint lcdLastUpdate;

WebServer* ws;
DHTWrapper* dht;
LCDWrapper* lcd;
SoilSensor* soilSensor;
IRWrapper* ir;
uint32_t command;

void setup() {
  Serial.setDebugOutput(true);
  Serial.begin(9600);

  dht = new DHTWrapper(DHT_PIN);
  lcd = new LCDWrapper(I2C_ADDRESS, DISPLAY_COLS, DISPLAY_ROWS, LCD_AUTOSCROLL);
  ir = new IRWrapper(IR_PIN);
  soilSensor = new SoilSensor(SOIL_SENSOR_PIN);
  initWebServer();

  lcdLastUpdate = millis() / 1000;
}

void loop() {
  ws->listen();
  if(uint32_t res = ir->getInput()) {
    if(res == IRWrapper::Key::POWER) {
      lcd->toggle();
    }    
  }

  // It will eventually overflow but it might just skip an update and restart from 0
  now = millis() / 1000;
  if (now - lcdLastUpdate >= LCD_PERIOD_SEC) {
    // lcd->display(0, 0, dht->update());
    lcd->display(0, 0, String("Uptime: ") + String(now));
    lcd->display(1, 0, String("Soil: ") + String(soilSensor->get_humidity()));
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
