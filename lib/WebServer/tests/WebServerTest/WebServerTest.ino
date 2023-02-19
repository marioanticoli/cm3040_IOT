#line 2 "WebServerTest.ino"

#include <AUnit.h>
#include "WebServer.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "WifiCredentials.h"

using namespace aunit;

// in setup, we prepare the serial port.
void setup() {
  Serial.setDebugOutput(true);
  Serial.begin(9600);
  while (!Serial)
    ;
  TestRunner::setTimeout(60);
}

// we just call the test runner in loop
void loop() {
  TestRunner::run();
}

class CustomTestOnce : public TestOnce {
protected:
  WebServer* ws = new WebServer();
  HTTPClient http;
  std::map<String, std::tuple<String, int, String (*)(String), String>> r = {
    { "", std::make_tuple("GET", 200, &home, "text/html") }
  };

  void setup() override {
    TestOnce::setup();
    ws->setRoutes(r);
  }

  void assertStatus() {
    assertTrue(ws->getStatus().equals("Disconnected"));
    connect();
    assertTrue(ws->getStatus().equals("Connected"));
  }

  void assertConnect() {
    assertTrue(ws->getStatus().equals("Disconnected"));
    ws->connect(SSID, PASSWORD);
    while (ws->getStatus() != "Connected") {
      delay(500);
    }
    assertTrue(ws->getStatus().equals("Connected"));
  }

  void assertNotFound() {
    ws->listen();
    String ip = connect();
    WiFiClient client;
    http.begin(client, "http://" + ip + "/inexistent");
    int status = http.GET();
    String expected = "<h1>Not Found</h1>";

    String resp = http.getString();

    assertEqual(resp, expected);
  }

  void assertGetReq() {
    ws->listen();
    String ip = connect();
    WiFiClient client;
    http.begin(client, "http://" + ip);
    int status = http.GET();
    String expected = "Home";

    String resp = http.getString();

    assertEqual(resp, expected);
  }

  String connect() {
    ws->connect(SSID, PASSWORD);
    while (ws->getStatus() != "Connected") {
      delay(500);
    }
    ws->start();
    return ws->getIPAddress().toString();
  }

  // dummy callback
  static String home(String arg) {
    return "Home";
  }
};

testF(CustomTestOnce, assertStatus) {
  assertStatus();
}

testF(CustomTestOnce, assertConnect) {
  assertConnect();
}

testF(CustomTestOnce, assertNotFound) {
  assertNotFound();
}

testF(CustomTestOnce, assertGetReq) {
  assertGetReq();
}
