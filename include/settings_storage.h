#ifndef SETTINGS_STORAGE_H
#define SETTINGS_STORAGE_H

#include <Arduino.h>

struct WiFiCredentials {
  String ssid;
  String password;

  bool isValid() const {
    return ssid.length() > 0 && password.length() > 0;
  }
};

bool saveWiFiCredentials(const WiFiCredentials &creds);
WiFiCredentials loadWiFiCredentials();

#endif
