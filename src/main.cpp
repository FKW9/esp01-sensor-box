#include <Arduino.h>
#include "graphite.h"
#include "hte501.h"
#include "config.h"
#include "display.h"

#ifndef DEBUG
bool buttonWakeup = false;
#else
bool buttonWakeup = true;
#endif

float rht[] = {0, 0};
String metrics[] = {GRAPHITE_RH, GRAPHITE_T};

unsigned long previous_millis = 0;
#define DISPLAY_SHOW_TIME 5000

void setup()
{
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1);

#ifndef DEBUG
  // detect if button was pressed for wake up
  pinMode(1, INPUT);

  if (digitalRead(1) == 0)
  {
    // button wakeup
    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
    delay(400);
    digitalWrite(3, HIGH);
    buttonWakeup = true;

    // power saving
    pinMode(1, INPUT_PULLUP);
  }
  else
  {
    // rtc wakeup
  }
#else
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  Serial.println("\r\nEntered DEBUG mode!");
#endif

  setupSensor();

  // setup display when user pressed button
  if (buttonWakeup)
  {
    setupDisplay();
  }

  // read sensor, then setup WiFi and send data
  if (getTemperatureHumidity(rht[1], rht[0]))
  {

    // when user pressed button, display data immediately
    if (buttonWakeup)
    {
      previous_millis = millis();
      displayTemperatureHumidity(rht[1], rht[0]);
    }

    // try to connect to WiFi
    if (setupWiFi())
    {
      // try to send data to server
      if (submitToGraphite(metrics, rht, 2))
      {
        exitWiFi();
        // blink led to indicate successfull data transmission
        if (buttonWakeup)
        {
          digitalWrite(3, LOW);
          delay(150);
          digitalWrite(3, HIGH);
          delay(100);
          digitalWrite(3, LOW);
          delay(150);
          digitalWrite(3, HIGH);
        }
      }
      else
      {
        exitWiFi();
        // sending data to graphite failed
        delay(1000);
        displayError("Send Err");
        delay(1000);
      }
    }
    else
    {
      exitWiFi();
      // wifi setup failed
      displayError("WiFi Err");
      delay(1000);
    }

  }
  else
  {
    // getting sensor data failed
    displayError("Sens Err");
  }

  // shut down display after some time
  if (buttonWakeup)
  {
    if (millis() - previous_millis >= DISPLAY_SHOW_TIME)
    {
      exitDisplay(0);
    }
    else
    {
      exitDisplay(DISPLAY_SHOW_TIME - (millis() - previous_millis));
    }
  }

  // power saving
  pinMode(0, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  // go to sleep
  ESP.deepSleep(SLEEP_TIME, WAKE_RF_DISABLED);
}

void loop() {}
