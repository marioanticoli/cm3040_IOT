#ifndef WebServer_h
#define WebServer_h
#pragma once
#include <ESP8266WebServer.h>
#include <map>
#include <tuple>

// Class to manage a simple WebServer
// It can respond to GET and POST of user-defined routes

class WebServer {
private:
  std::map<String, std::tuple<String, int, String (*)(), String>> routes;
  ESP8266WebServer server;

  void handleRequest(String, String);

public:
  // Initialise the webserver to given port (default 80)
  WebServer(uint16_t = 80);
  // Connect to the wifi
  void connect(const char*, const char*);
  // Start webserver
  bool start();
  // Stop webserver
  void stop();
  // Get connection status
  String getStatus();
  // Get local IP address
  IPAddress getIPAddress();
  // Accepts incoming requests
  void listen();
  // Set user-defined routes
  void setRoutes(std::map<String, std::tuple<String, int, String (*)(), String>>);
};

#endif
