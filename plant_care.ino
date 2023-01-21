#include "WebServer.h"
#include "WifiCredentials.h"
#include <map>
#include <tuple>
#include "DHTWrapper.h"
#include "LCDWrapper.h"
#include "AnalogReader.h"
#include "IRWrapper.h"
#include "RelayController.h"
#include "DigitalOutput.h"

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
#define MUX_PIN D7  // Using 1 pin instead of canonical 3 allows me to control two inputs on the multiplexer, remaining PINs are set to 0 (GND)
#define LED_PIN D8
#define SOIL_SENSOR_PIN A0
#define PHOTO_PIN A0

#define DRY_VALUE 740
#define WET_VALUE 288
#define DARK_VALUE 1
#define LIGHT_VALUE 100

#define LCD_PERIOD_MS 1000

uint now;
// LCD last updated time
uint lcdLastUpdate;

// Declare objects in global scope
WebServer* ws;
DHTWrapper* dht;
LCDWrapper* lcd;
AnalogReader* soilSensor;
AnalogReader* photo;
IRWrapper* ir;
RelayController* pump;
DigitalOutput* mux;
DigitalOutput* led;

// Holds the input from the IR receiver
uint32_t command;

void setup() {
  // Serial.setDebugOutput(true);
  Serial.begin(9600);

  // Initialise sensors, relays and outputs
  pump = new RelayController(WATER_PUMP_PIN);
  dht = new DHTWrapper(DHT_PIN);
  lcd = new LCDWrapper(I2C_ADDRESS, DISPLAY_COLS, DISPLAY_ROWS, LCD_AUTOSCROLL);
  ir = new IRWrapper(IR_PIN);
  soilSensor = new AnalogReader(SOIL_SENSOR_PIN, WET_VALUE, DRY_VALUE);
  photo = new AnalogReader(PHOTO_PIN, DARK_VALUE, LIGHT_VALUE);
  mux = new DigitalOutput(MUX_PIN);
  led = new DigitalOutput(LED_PIN);

  initWebServer();

  lcdLastUpdate = millis() / 1000;
}

void loop() {
  now = millis();

  // Listen to incoming requests to the webserver
  ws->listen();

  // Check if IR received a command and pass it to a Menu instance
  if (uint32_t res = ir->getInput()) {
    // TODO: pass res to menu
  }

  long soilHum = soilSensor->get_perc_value();
  long light = photo->get_perc_value();
  // TODO: pass to plantSettings and check if need water and/or light

  if (now - lcdLastUpdate >= LCD_PERIOD_MS) {
    // TODO: if menu off show sensor data
    // else show menu
    lcdLastUpdate = now;
  }
}

void showSensorDate() {
  // TODO
  lcd->display(0, 0, dht->update());
  lcd->display(1, 0, String("Soil: ") + String(humidity));
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
    { "", std::make_tuple("GET", 200, &status) },
    // TODO: check status code
    { "/light", std::make_tuple("POST", 200, &setLights) },
    { "/pump", std::make_tuple("POST", 200, &setPump) },
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
String status() {
  // TODO: give a good overview
  return "<h2>" + dht->update() + "</h2>";
}

String setLights() {
  // TODO
}

String setPump() {
  // TODO
}
