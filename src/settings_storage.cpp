#include "settings_storage.h"
#include <LittleFS.h>
#include <ArduinoJson.h>

#define WIFI_CONFIG_FILE "/wifi.json"

bool saveWiFiCredentials(const WiFiCredentials &creds) {
  File file = LittleFS.open(WIFI_CONFIG_FILE, "w");
  if (!file) {
    Serial.println("❌ Impossible d'ouvrir le fichier pour écriture");
    return false;
  }

  StaticJsonDocument<256> doc;
  doc["ssid"] = creds.ssid;
  doc["password"] = creds.password;

  if (serializeJson(doc, file) == 0) {
    Serial.println("❌ Échec de l’écriture JSON");
    file.close();
    return false;
  }

  file.close();
  Serial.println("✅ Données Wi-Fi enregistrées dans /wifi.json");
  return true;
}

WiFiCredentials loadWiFiCredentials() {
  WiFiCredentials creds;

  if (!LittleFS.exists(WIFI_CONFIG_FILE)) {
    Serial.println("ℹ️ Fichier Wi-Fi non trouvé");
    return creds;
  }

  File file = LittleFS.open(WIFI_CONFIG_FILE, "r");
  if (!file) {
    Serial.println("❌ Impossible d’ouvrir le fichier pour lecture");
    return creds;
  }

  StaticJsonDocument<256> doc;
  DeserializationError err = deserializeJson(doc, file);
  file.close();

  if (err) {
    Serial.println("❌ Échec de la lecture du JSON");
    return creds;
  }

  creds.ssid = doc["ssid"].as<String>();
  creds.password = doc["password"].as<String>();
  return creds;
}
