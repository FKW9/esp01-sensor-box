#define SLEEP_TIME      1800e6  // in micro seconds

#define GRAPHITE_HOST "192.168.8.42"
#define GRAPHITE_PORT 2003

#define GRAPHITE_RH "sensor.sensor_box.rh"
#define GRAPHITE_T 	"sensor.sensor_box.t"

#define WIFI_KEY    "<YOUR WIFI KEY>"
#define WIFI_SSID   "<YOUR WIFI SSID>"
#define WIFI_CH     9                  // channel to use

// following settings are needed for a fast wifi connection
// change for your router!
// attention: if you have a WiFi Mesh or similar, each AP has their own BSSID: Choose the closest to the device!
const uint8_t WIFI_BSSID[6] = {0x7E, 0xD2, 0x94, 0x3B, 0x21, 0xA8};

const IPAddress LOCAL_IP(192, 168, 8, 23);
const IPAddress GATEWAY_IP(192, 168, 8, 1);
const IPAddress SUBNET_IP(255, 255, 255, 0);
const IPAddress DNS_IP(8, 8, 8, 8);

