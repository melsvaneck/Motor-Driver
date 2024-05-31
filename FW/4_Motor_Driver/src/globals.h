#ifndef __GLOBALS_H
#define __GLOBALS_H

#include "gui.h"
#include "settings.h"
#include "M5UnitHbridge.h"

extern settings_t settings;
extern SettingsManager setman;
extern GUI gui;


extern bool motorOn[5];
extern double motorSpeed[NUMBER_OF_MOTORS];

extern float vin_raw[NUMBER_OF_MOTORS];
extern float cin_raw[NUMBER_OF_MOTORS];

extern M5UnitHbridge* drvs[NUMBER_OF_CHANNELS];
extern M5UnitHbridge driver1;

#endif //__GLOBALS_H
