#include "capteur_niveau.h"

#define PIN_CAPTEUR_NIVEAU D5  // À adapter selon ton câblage

void initCapteurNiveau() {
    pinMode(PIN_CAPTEUR_NIVEAU, INPUT_PULLUP);  // Assumes switch to GND when low
}

void updateNiveauCroquette(SystemStatus &status) {
    bool niveauBas = digitalRead(PIN_CAPTEUR_NIVEAU) == LOW;

    if (niveauBas) {
        status.niveauCroquette = CROQ_CRITIQUE;
    } else {
        status.niveauCroquette = CROQ_OK;
    }
}
