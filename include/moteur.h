#ifndef MOTEUR_H
#define MOTEUR_H

#include <Arduino.h>

class Moteur {
public:
  Moteur();

  void init();
  void startDistribution(unsigned long duree_ms);
  void update();
  
  // Pour futur contrôle par capteur rotation
  void enableCapteurRotation(bool enabled);
  void onRotationPulse();

  bool estEnCours() const;

private:
  static const uint8_t RELAIS_PIN = D5;  // <-- Définition centralisée ici

  bool _enDistribution = false;
  unsigned long _debutDistribution = 0;
  unsigned long _dureeDistribution = 0;

  bool _capteurRotationActive = false;
  volatile unsigned int _impulsions = 0;
  unsigned int _impulsionsCible = 0;

  void arreterMoteur();
};

#endif
