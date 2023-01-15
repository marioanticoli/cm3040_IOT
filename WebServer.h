#ifndef WebServer_h
#define WebServer_h
#pragma once
#include <ESP8266WebServer.h>
#include <map>

class WebServer {
  private:
    ESP8266WebServer server;
    void handleRequest(String);
    String buildHTML(String);

  public:
    WebServer();
    void connect(const char*, const char*);
    bool start();
    void stop();
    String getStatus();
    IPAddress getIPAddress();
    void listen();
};

#endif
