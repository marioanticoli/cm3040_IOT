#ifndef WebServer_h
#define WebServer_h
#pragma once
#include <ESP8266WebServer.h>
#include <map>
#include <tuple>
#include <string>

// Class to manage a simple WebServer
// It can respond to GET and POST of user-defined routes

class WebServer {
private:
  // Map of tuple containing method, status code, pointer to function
  std::map<std::string, std::tuple<std::string, int, std::string (*)(std::string*, uint8_t), std::string*, uint8_t>> routes;
  ESP8266WebServer server;
  std::string openHTML;
  std::string closeHTML;

  void handleRequest(std::string, std::string);
  std::string buildHTML(std::string);

public:
  // Initialise the webserver to given port (default 80)
  WebServer(std::string, std::string, uint16_t = 80);
  // Connect to the wifi
  void connect(const char*, const char*);
  // Start webserver
  bool start();
  // Stop webserver
  void stop();
  // Get connection status
  std::string getStatus();
  // Get local IP address
  IPAddress getIPAddress();
  // Accepts incoming requests
  void listen();
  // Set user-defined routes
  void setRoutes(std::map<std::string, std::tuple<std::string, int, std::string (*)(std::string*, uint8_t), std::string*, uint8_t>>);
};

#endif
