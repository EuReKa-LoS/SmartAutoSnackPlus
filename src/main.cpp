#include <ESP8266WiFi.h>
#include "status.h"
#include "capteur_niveau.h"
#include "leds.h"
#include "moteur.h"
#include "wifi_manager.h"


SystemStatus status;
Moteur moteur;  // Utilisation du constructeur par défaut

unsigned long lastDistribution = 0;

void setup() {

  Serial.begin(115200);
  delay(10000);
  Serial.println("Initialisation SmartAutoSnackPlus...");
  initWiFi();

  initCapteurNiveau();
  initLeds();
  moteur.init();

  //testLeds();
}

void loop() {
  //Serial.print("Boucle principale en cours...\n");
  unsigned long now = millis();
  updateWiFiStatus(status);
  updateNiveauCroquette(status);
  updateLeds(status);
  updateWifiLed(status);


  if (!moteur.estEnCours() && (now - lastDistribution > 10000)) {
    moteur.startDistribution(3000);  // Distribue pendant 3 secondes
    lastDistribution = now;
  }

  moteur.update();

  delay(100);
  
}
