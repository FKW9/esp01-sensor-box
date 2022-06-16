#include <ESP8266WiFi.h>

int setupWiFi(void);
int submitToGraphite(String metrics[], float values[], uint8_t length);
void exitWiFi(void);