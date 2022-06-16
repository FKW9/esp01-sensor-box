#include "SSD1306Wire.h"

extern SSD1306Wire display;

void setupDisplay();
void displayTemperatureHumidity(float t, float rh);
void displayError(String message);
void exitDisplay(float exit_delay);
