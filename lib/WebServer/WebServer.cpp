#include "Arduino.h"
#include "WebServer.h"

WebServer::WebServer(char *ssid, char *password) : server(80)
{
    WiFi.begin(ssid, password);

    server.on("/", [this]() {
        server.send(200, "text/plain", "Hello World");
    });
    
    server.begin();
}

String WebServer::getStatus()
{
    switch (WiFi.status())
    {
    case WL_CONNECTED:
        return "Connected";
        break;
    case WL_NO_SHIELD:
        return "No shield";
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
        break;
    }
}

IPAddress WebServer::getIPAddress()
{
    return WiFi.localIP();
}
