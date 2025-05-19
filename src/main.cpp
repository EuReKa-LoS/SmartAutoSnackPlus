#include <ESP8266WiFi.h>
#include "status.h"
#include "capteur_niveau.h"
#include "leds.h"
#include "moteur.h"

// Utilisation des variables d'environnement (PlatformIO build_flags)
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

SystemStatus status;
Moteur moteur;  // Utilisation du constructeur par défaut

unsigned long lastDistribution = 0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  initCapteurNiveau();
  initLeds();
  moteur.init();

  testLeds();
}

void loop() {
  unsigned long now = millis();

  updateNiveauCroquette(status);
  updateLeds(status);

  if (!moteur.estEnCours() && (now - lastDistribution > 10000)) {
    moteur.startDistribution(3000);  // Distribue pendant 3 secondes
    lastDistribution = now;
  }

  moteur.update();

  delay(100);
}
