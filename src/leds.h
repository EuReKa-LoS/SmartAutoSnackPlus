#ifndef LEDS_H
#define LEDS_H

#include "status.h"

void initLeds();
void updateLeds(const SystemStatus &status);

#endif
