#include <ESP8266WiFi.h>

// Utilisation des variables d'environnement
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  // Ton code ici
}
