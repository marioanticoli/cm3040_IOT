#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <uri/UriBraces.h>
#include "WebServer.h"

WebServer::WebServer(std::string openHTML, std::string closeHTML, uint16_t port)
  : server(port), openHTML(openHTML), closeHTML(closeHTML) {
}

void WebServer::connect(const char *ssid, const char *password) {
  WiFi.begin(ssid, password);
}

void WebServer::setRoutes(std::map<std::string, std::tuple<std::string, int, std::string (*)(std::string*, uint8_t), std::string*, uint8_t>> routes) {
  this->routes = routes;
}

bool WebServer::start() {
  if (WiFi.isConnected()) {
    server.on(UriBraces("/{}"), HTTP_GET, [this]() {      
      handleRequest(server.pathArg(0).c_str(), "GET");
    });
    server.on(UriBraces("/{}"), HTTP_POST, [this]() {
      handleRequest(server.pathArg(0).c_str(), "POST");
    });
    server.begin();
    return true;
  } else {
    return false;
  }
}

std::string WebServer::getStatus() {
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

void WebServer::handleRequest(std::string uri, std::string method) {
  // Look for endpoint in the routes map
  auto it = routes.find(uri);

  int status;
  std::string response;

  auto values = it->second;
  // If a value was found in the map and the method matches
  if (it != routes.end() && method.compare(std::get<0>(values)) == 0) {
    // Get the status from the value of the map
    status = std::get<1>(values);
    // Get the function, pass it the parameters and their size to build the HTML with the resulting std::string
    auto params = std::get<3>(values);
    uint8_t size = std::get<4>(values);
    std::string innerHTML = std::get<2>(values)(params, size);
    response = buildHTML(innerHTML);
  } else {
    // If no routes found
    status = 404;
    response = buildHTML("<h2>Not Found</h2>");
  }

  server.send(status, "text/html", response.c_str());
}

std::string WebServer::buildHTML(std::string innerHTML) {
  return openHTML + innerHTML + closeHTML;
}
