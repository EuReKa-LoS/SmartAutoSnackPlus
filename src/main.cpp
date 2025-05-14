#include <ESP8266WiFi.h>
#include "status.h"
#include "capteur_niveau.h"
#include "leds.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

SystemStatus status;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("Connected to WiFi");
    
    // Initialisation des capteurs et LEDs
    initCapteurNiveau();
    initLeds();
}

void loop() {
    // Mise à jour du niveau des croquettes et de l'état des LEDs
    updateNiveauCroquette(status);
    updateLeds(status);

    delay(100);  // Anti-bounce
}
