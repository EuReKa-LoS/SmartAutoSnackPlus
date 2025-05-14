#include "capteur_niveau.h"
#include <Arduino.h>  // Inclure pour les fonctions delay() et Serial

// Définition des fonctions
void initCapteurNiveau() {
    pinMode(D2, INPUT);  // Exemple de pin, à ajuster selon ton matériel
}

void updateNiveauCroquette(SystemStatus &status) {
    int niveau = digitalRead(D2);  // Lire l'état du capteur de croquettes
    
    // Mise à jour du niveau de croquettes
    if (niveau == HIGH) {
        status.niveauCroquette = CROQ_OK;
    } else {
        status.niveauCroquette = CROQ_CRITIQUE;
    }
}
