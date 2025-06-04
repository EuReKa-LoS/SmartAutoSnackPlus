#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "status.h"

void initWiFi();
void updateWiFiStatus(SystemStatus &status);

class WiFiManagerCustom {
public:
    void begin();                  // Lance le Wi-Fi en mode config ou STA
    void setDebugMode(bool debug); // Force le mode config pour debug

private:
    bool debugMode = false;
    void startAccessPoint();      // Mode config via AP
    void connectToWiFi();         // Mode station
};

extern WiFiManagerCustom wifi_manager;


#endif