#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <uri/UriBraces.h>
#include "WebServer.h"

WebServer::WebServer()
  : server(80) {
}

void WebServer::connect(const char *ssid, const char *password) {
  WiFi.begin(ssid, password);
}

bool WebServer::start() {
  if (WiFi.isConnected()) {
    // server.addHandler(&globHandler);
    server.on(UriBraces("/{}"), [this]() {
      handleRequest(server.pathArg(0));
    });
    server.begin();
    return true;
  } else {
    return false;
  }
}

String WebServer::getStatus() {
  switch (WiFi.status()) {
    case WL_CONNECTED:
      return "Connected";
      break;
    case WL_NO_SHIELD:
      return "No shield";
      break;
    case WL_IDLE_STATUS:
      return "Idle";
      break;
    case WL_NO_SSID_AVAIL:
      return "No SSID available";
      break;
    case WL_SCAN_COMPLETED:
      return "Scan network completed";
      break;
    case WL_CONNECT_FAILED:
      return "Connection failed";
      break;
    case WL_CONNECTION_LOST:
      return "Connection lost";
      break;
    case WL_DISCONNECTED:
      return "Disconnected";
      break;
    default:
      return "Unknown status";
  }
}

IPAddress WebServer::getIPAddress() {
  return WiFi.localIP();
}

void WebServer::listen() {
  server.handleClient();
}

void WebServer::stop() {
  server.stop();
  WiFi.disconnect();
}

void WebServer::handleRequest(String uri) {
  String response;
  int status;
  if (uri == "") {
    response = buildHTML("<h2>home</h2>");
    status = 200;
  } else {
    response = buildHTML("<h2>Not Found</h2>");
    status = 404;
  }
  server.send(status, "text/html", response);
}

String WebServer::buildHTML(String innerHTML) {
  String html = 
    "<!DOCTYPE html><html><head><meta http-equiv=\"refresh\" content=\"2\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"></head><body> <h1>Plant Care Dashboard</h1>"
    + innerHTML
    + "</body></html>";

  return html;
}
