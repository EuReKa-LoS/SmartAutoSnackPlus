#include "leds.h"

#define PIN_LED_ROUGE D6  // À adapter selon ton câblage

void initLeds() {
    pinMode(PIN_LED_ROUGE, OUTPUT);
    digitalWrite(PIN_LED_ROUGE, LOW);
}

void updateLeds(const SystemStatus &status) {
    if (status.niveauCroquette == CROQ_CRITIQUE) {
        digitalWrite(PIN_LED_ROUGE, HIGH);  // Allume la LED rouge
    } else {
        digitalWrite(PIN_LED_ROUGE, LOW);   // Éteint la LED rouge
    }
}
