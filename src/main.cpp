#include <ESP8266WiFi.h>
#include "status.h"
#include "capteur_niveau.h"
#include "leds.h"
#include "moteur.h"
#include "wifi_manager.h"
#include <LittleFS.h>


SystemStatus status;
Moteur moteur;  // Utilisation du constructeur par défaut

unsigned long lastDistribution = 0;

void setup() {
  // Montage LittleFS pour lire/écrire les fichiers de configuration
  if (!LittleFS.begin()) {
  Serial.println("Erreur de montage LittleFS !");
  }

  Serial.begin(115200);
  delay(10000);
  Serial.println("Initialisation SmartAutoSnackPlus...");
  wifi_manager.setDebugMode(true); // Forcer mode config au boot
  wifi_manager.begin();            // Lance le bon mode (STA ou AP)

  initCapteurNiveau();
  initLeds();
  moteur.init();

  //testLeds();
}

void loop() {
  
  //Serial.print("Boucle principale en cours...\n");
  unsigned long now = millis();
  if (!wifi_manager.isInConfigMode()) {
    updateWiFiStatus(status);
  }
  wifi_manager.handleClient();
  updateNiveauCroquette(status);
  updateLeds(status);
  updateWifiLed(status);
  // Debug purpose
  // Serial.println("Lecture du fichier de configuration Wi-Fi...");
  // Lire le fichier de configuration Wi-Fi
  // Afficher le contenu du fichier
  /*
  File f = LittleFS.open("/wifi.json", "r");
  if (f) {
    while (f.available()) {
      Serial.write(f.read());
    }
    f.close();
  }*/
  


  if (!moteur.estEnCours() && (now - lastDistribution > 10000)) {
    moteur.startDistribution(3000);  // Distribue pendant 3 secondes
    lastDistribution = now;
  }

  moteur.update();

  delay(100);
  
}
