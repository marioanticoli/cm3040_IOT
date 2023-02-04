#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <uri/UriBraces.h>
#include "WebServer.h"

WebServer::WebServer(String openHTML, String closeHTML, uint16_t port)
  : server(port), openHTML(openHTML), closeHTML(closeHTML) {
}

void WebServer::connect(const char *ssid, const char *password) {
  WiFi.begin(ssid, password);
}

void WebServer::setRoutes(std::map<String, std::tuple<String, int, String (*)(String*, uint8_t), String*, uint8_t>> routes) {
  this->routes = routes;
}

bool WebServer::start() {
  if (WiFi.isConnected()) {
    server.on(UriBraces("/{}"), HTTP_GET, [this]() {      
      handleRequest(server.pathArg(0), "GET");
    });
    server.on(UriBraces("/{}"), HTTP_POST, [this]() {
      handleRequest(server.pathArg(0), "POST");
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

void WebServer::handleRequest(String uri, String method) {
  // Look for endpoint in the routes map
  auto it = routes.find(uri);

  int status;
  String response;

  auto values = it->second;
  Serial.println(std::get<0>(values));
  // If a value was found in the map and the method matches
  if (it != routes.end() && method.equalsIgnoreCase(std::get<0>(values))) {
    // Get the status from the value of the map
    status = std::get<1>(values);
    // Get the function, pass it the parameters and their size to build the HTML with the resulting String
    auto params = std::get<3>(values);
    uint8_t size = std::get<4>(values);
    String innerHTML = std::get<2>(values)(params, size);
    response = buildHTML(innerHTML);
  } else {
    // If no routes found
    status = 404;
    response = buildHTML("<h2>Not Found</h2>");
  }

  server.send(status, "text/html", response);
}

String WebServer::buildHTML(String innerHTML) {
  return openHTML + innerHTML + closeHTML;
}
