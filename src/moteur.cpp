#include "moteur.h"

Moteur::Moteur(uint8_t pinRelais) : _pinRelais(pinRelais) {}

void Moteur::init() {
  pinMode(_pinRelais, OUTPUT);
  digitalWrite(_pinRelais, LOW); // Moteur éteint au départ
}

void Moteur::startDistribution(unsigned long duree_ms) {
  _debutDistribution = millis();
  _dureeDistribution = duree_ms;
  _enDistribution = true;
  digitalWrite(_pinRelais, HIGH); // Active relais/moteur
  _impulsions = 0;                // Reset compteur impulsions
}

void Moteur::update() {
  if (!_enDistribution) return;

  if (_capteurRotationActive) {
    // Futur traitement basé sur comptage impulsions (non implémenté ici)
    // Exemple : if (_impulsions >= _impulsionsCible) arreterMoteur();
  } else {
    // Mode simple temporisation
    if (millis() - _debutDistribution >= _dureeDistribution) {
      arreterMoteur();
    }
  }
}

void Moteur::enableCapteurRotation(bool enabled) {
  _capteurRotationActive = enabled;
  _impulsions = 0;
}

void Moteur::onRotationPulse() {
  if (_capteurRotationActive) {
    _impulsions++;
  }
}

void Moteur::arreterMoteur() {
  digitalWrite(_pinRelais, LOW);
  _enDistribution = false;
}

bool Moteur::estEnCours() const {
  return _enDistribution;
}
