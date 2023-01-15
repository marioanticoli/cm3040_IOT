#ifndef WebServer_h
#define WebServer_h
#pragma once
#include <ESP8266WebServer.h>
#include <map>
#include <tuple>

class WebServer {
  private:
    // Map of tuple containing method, status code, pointer to function
    std::map<String, std::tuple<String, int, String (*)()>> routes;
    ESP8266WebServer server;
    void handleRequest(String, String);
    String buildHTML(String);

  public:
    WebServer();
    void connect(const char*, const char*);
    bool start();
    void stop();
    String getStatus();
    IPAddress getIPAddress();
    void listen();
    void setRoutes(std::map<String, std::tuple<String, int, String (*)()>>);
    long getSignal();
};

#endif
