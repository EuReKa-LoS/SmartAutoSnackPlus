#include "moteur.h"

Moteur::Moteur() {}

void Moteur::init() {
  pinMode(RELAIS_PIN, OUTPUT);
  digitalWrite(RELAIS_PIN, LOW);  // S'assurer que le moteur est arrêté
}

void Moteur::startDistribution(unsigned long duree_ms) {
  _dureeDistribution = duree_ms;
  _debutDistribution = millis();
  _enDistribution = true;
  digitalWrite(RELAIS_PIN, HIGH);
}

void Moteur::update() {
  if (_enDistribution && (millis() - _debutDistribution >= _dureeDistribution)) {
    arreterMoteur();
  }
}

void Moteur::arreterMoteur() {
  digitalWrite(RELAIS_PIN, LOW);
  _enDistribution = false;
}

void Moteur::enableCapteurRotation(bool enabled) {
  _capteurRotationActive = enabled;
  if (!enabled) {
    _impulsions = 0;
  }
}

void Moteur::onRotationPulse() {
  if (_capteurRotationActive) {
    _impulsions++;
    if (_impulsions >= _impulsionsCible) {
      arreterMoteur();
    }
  }
}

bool Moteur::estEnCours() const {
  return _enDistribution;
}
// Note: Le capteur de rotation n'est pas encore implémenté dans ce code.
// Il faudra ajouter la logique pour définir le nombre d'impulsions cible