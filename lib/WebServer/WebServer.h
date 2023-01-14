#ifndef WebServer_h
#define WebServer_h
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

class WebServer {
  private:
    int status;
    ESP8266WebServer server;

  public:
    WebServer(char*, char*);
    String getStatus();
    IPAddress getIPAddress();
};

#endif
