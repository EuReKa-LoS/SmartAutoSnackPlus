#include <ESP8266WiFi.h>
#include "status.h"
#include "capteur_niveau.h"
#include "leds.h"
#include "moteur.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
SystemStatus status;
Moteur moteur(D1); // Pin relais moteur, à adapter

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  initCapteurNiveau();
  initLeds();
  moteur.init();
}

void loop() {
  updateNiveauCroquette(status);
  updateLeds(status);
  moteur.update();

  // Exemple simple : lancer distribution 2 secondes dès que le moteur est à l'arrêt
  if (!moteur.estEnCours()) {
    moteur.startDistribution(2000);
  }

  delay(100);
}
