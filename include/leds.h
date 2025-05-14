#ifndef LEDS_H
#define LEDS_H

#include "status.h"

// Déclaration des fonctions
void initLeds();
void updateLeds(const SystemStatus &status);

#endif
