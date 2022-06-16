#include "display.h"
#include "font.h"

SSD1306Wire display(0x3C, 2, 0, GEOMETRY_64_32);

void setupDisplay()
{
  display.init();
  // display.flipScreenVertically();
  display.setFont(DejaVu_Sans_Mono_Bold_14);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
}

void displayTemperatureHumidity(float t, float rh){
  display.drawString(32, 1,  String(t, 1)  + "°C");
  display.drawString(32, 17, String(rh, 1) + " %");
  display.display();
}

void displayError(String message){
  display.clear();
  display.drawString(32, 11, message);
  display.display();
}

void exitDisplay(float exit_delay){
  delay(exit_delay);
  display.end();
  display.displayOff();
}
