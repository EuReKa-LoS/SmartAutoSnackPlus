#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "status.h"

//Legcy keep for debuging purposes
// Commented out to avoid confusion, as we are using a custom WiFiManager class now
// This function is not used anymore, but can be uncommented if needed for debugging
//void initWiFi();
void updateWiFiStatus(SystemStatus &status);

class WiFiManagerCustom {
public:
    void begin();                  // Lance le Wi-Fi en mode config ou STA
    void setDebugMode(bool debug); // Force le mode config pour debug
    void handleClient();
    bool isInConfigMode() const { return inConfigMode; }  // Ou une variable dédiée

private:
    bool debugMode = false;
    bool inConfigMode = false;
    void startAccessPoint();      // Mode config via AP
    void connectToWiFi();         // Mode station
    ESP8266WebServer server = ESP8266WebServer(80); // Serveur HTTP sur le port 80
};

extern WiFiManagerCustom wifi_manager;


#endif