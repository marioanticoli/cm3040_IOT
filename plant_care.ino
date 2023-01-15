// #include <LiquidCrystal_I2C.h>

// LiquidCrystal_I2C lcd(0x27, 16, 2)
#include "WebServer.h"
#include "WifiCredentials.h"

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

void initWebServer() {
  ws.connect(SSID, PASSWORD);
  while(ws.getStatus() != "Connected") {
    Serial.println(ws.getStatus());
    delay(500);
  }
  Serial.println(ws.getStatus() + " with IP " + ws.getIPAddress().toString().c_str());
  if(ws.start()) {
    Serial.println("Started webserver");
  } else {
    Serial.println("Couldn't start the webserver.");
  }
}



// void displayData(String msg, int line, int column) {
//   lcd.setCursor(line, column);
//   lcd.print(msg);
// }
