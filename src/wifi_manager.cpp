#include "wifi_manager.h"
#include <Arduino.h>

// Constantes tirées des variables d'environnement
// Utilisation des variables d'environnement (PlatformIO build_flags)
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;

void initWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Tentative de connexion à : ");
  Serial.print(ssid);
}

void updateWiFiStatus(SystemStatus &status) {
  static unsigned long lastPrint = 0;
  static unsigned long lastReconnectAttempt = 0;
  unsigned long now = millis();

  wl_status_t wifiState = WiFi.status();

  if (wifiState == WL_CONNECTED) {
    if (!status.wifiConnected) {
      Serial.println("\nWi-Fi connecté !");
      Serial.print("IP locale : ");
      Serial.println(WiFi.localIP());
    }
    status.wifiConnected = true;
  } else {
    status.wifiConnected = false;
    if (now - lastPrint > 1000) {
      Serial.print(".");
      lastPrint = now;
    }
    // Relancer la connexion toutes les 10 secondes si déconnecté
    if (now - lastReconnectAttempt > 10000) {
      Serial.println("\nTentative reconnexion Wi-Fi...");
      WiFi.disconnect();  // On se déconnecte proprement avant de relancer
      WiFi.begin(ssid, password);
      lastReconnectAttempt = now;
    }
  }
}
