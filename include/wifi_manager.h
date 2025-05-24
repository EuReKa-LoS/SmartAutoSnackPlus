#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <ESP8266WiFi.h>
#include "status.h"

void initWiFi();
void updateWiFiStatus(SystemStatus &status);

#endif
