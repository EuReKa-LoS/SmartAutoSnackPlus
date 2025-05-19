#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>
#include "status.h"

// Définition des pins des LEDs
#define PIN_LED_ROUGE 12
#define PIN_LED_BLEU 13
#define PIN_LED_VERT 14

void initLeds();
void updateLeds(const SystemStatus &status);
void testLeds();

#endif
