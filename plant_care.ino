#include "WebServer.h"
#include "WifiCredentials.h"
#include <map>
#include <tuple>
#include "DHTWrapper.h"
#include "LCDWrapper.h"

#define DHT_PIN D5
#define I2C_ADDRESS 0x27
#define DISPLAY_COLS 16
#define DISPLAY_ROWS 2

WebServer* ws;
DHTWrapper* dht;
LCDWrapper* lcd;

void setup() {
  Serial.setDebugOutput(true);
  Serial.begin(9600);

  dht = new DHTWrapper(DHT_PIN);
  lcd = new LCDWrapper(I2C_ADDRESS, DISPLAY_COLS, DISPLAY_ROWS);
  lcd->display(0, 0, String("INIT LCD..."));
  initWebServer();
}

void loop() {
  ws->listen();
  dht->update();
  lcd->display(0, 0, String("Temp.: ") + String(dht->getTemperature(), 2));
  lcd->display(1, 0, String("Hum.: ") + String(dht->getHumidity(), 2));
  delay(1000);
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
