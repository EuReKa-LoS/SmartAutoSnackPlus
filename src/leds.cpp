#include "leds.h"
#include <Arduino.h>

void initLeds() {
    pinMode(LED_BUILTIN, OUTPUT);  // Exemple pour LED intégrée
}

void updateLeds(const SystemStatus &status) {
    // Mise à jour de l'état de la LED selon le niveau de croquettes
    if (status.niveauCroquette == CROQ_OK) {
        digitalWrite(LED_BUILTIN, LOW);  // LED verte allumée
    } else {
        digitalWrite(LED_BUILTIN, HIGH);  // LED rouge allumée
    }
}
