#include "globals.h"

#include "gui.h"
#include "settings.h"

GUI gui;
settings_t settings;
SettingsManager setman(settings);

M5UnitHbridge driver1,driver2, driver3, driver4;
M5UnitHbridge* drvs[NUMBER_OF_CHANNELS] = {&driver1, &driver2, &driver3, &driver4};


float vin_raw[NUMBER_OF_MOTORS] = {0, 0, 0, 0};
float cin_raw[NUMBER_OF_MOTORS] = {0, 0, 0, 0};

bool motorOn[NUMBER_OF_MOTORS] = {0, 0, 0, 0};
double motorSpeed[NUMBER_OF_MOTORS] = {5, 5, 5, 5};
