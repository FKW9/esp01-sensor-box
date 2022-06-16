#include "graphite.h"
#include "config.h"

// Graphite Client
WiFiClient carbonClient;

// Connect to WiFi
int setupWiFi()
{
  // https://github.com/esp8266/Arduino/issues/3072#issuecomment-1004950986
  WiFi.forceSleepBegin();
  delay(1);
  WiFi.forceSleepWake();
  delay(1);
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);

  WiFi.config(
    LOCAL_IP,
    GATEWAY_IP,
    SUBNET_IP,
    DNS_IP
  );

  WiFi.begin(
    WIFI_SSID,
    WIFI_KEY,
    WIFI_CH,
    WIFI_BSSID,
    true
  );

  static uint8_t cnt = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    #ifdef DEBUG
      Serial.println(cnt);
    #endif

    if (cnt++ > 5) {
      #ifdef DEBUG
        Serial.println("Could not connect to WiFi!");
      #endif
      return 0;
    }
  }

  #ifdef DEBUG
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.channel());
    Serial.println(WiFi.BSSIDstr());
    Serial.println(WiFi.RSSI());
  #endif
  return 1;
}

void exitWiFi(void){
  WiFi.disconnect(true);
  delay(1);
}

// Send metrics to graphite with current unix time
int submitToGraphite(String metrics[], float values[], uint8_t length)
{
  if (!carbonClient.connect(GRAPHITE_HOST, GRAPHITE_PORT))
  {
    #ifdef DEBUG
      Serial.println("Connecting to graphite failed!");
    #endif
    return 0;
  }

  for (uint8_t i = 0; i < length; i++)
  {
    String body = metrics[i] + " " + values[i] + " -1\n";
    carbonClient.print(body);
    #ifdef DEBUG
      Serial.print(body);
    #endif
  }

  carbonClient.stop();
  return 1;
}
