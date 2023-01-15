// #include <LiquidCrystal_I2C.h>

// LiquidCrystal_I2C lcd(0x27, 16, 2)
#include "WebServer.h"
#include "WifiCredentials.h"
#include <map>
#include <tuple>

WebServer ws;

void setup() {
  // Serial.setDebugOutput(true);
  Serial.begin(9600);

  initWebServer();
  // lcd.init();
  // lcd.backlight();
}

void loop() {
  // displayData("prova", 0, 0);
  ws.listen();
}

/*
*******************
WebServer block
*******************
*/

void initWebServer() {
  // Create routes
  std::map<String, std::tuple<String, int, String (*)()>> r = {
    { "", std::make_tuple("GET", 200, &home) },
    { "status", std::make_tuple("GET", 200, &status) },
    { "set_status", std::make_tuple("POST", 200, &setStatus) }
  };

  ws.setRoutes(r);

  ws.connect(SSID, PASSWORD);
  while (ws.getStatus() != "Connected") {
    Serial.println(ws.getStatus());
    delay(500);
  }
  Serial.println(ws.getStatus() + " with IP " + ws.getIPAddress().toString().c_str());
  if (ws.start()) {
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
  return "<h2>Signal strength is" + String(ws.getSignal()) + "dB</h2>";
}

String setStatus() {
  return "<h2>POST request</h2>";
}

/*
*******************
End WebServer block
*******************
*/

// void displayData(String msg, int line, int column) {
//   lcd.setCursor(line, column);
//   lcd.print(msg);
// }
