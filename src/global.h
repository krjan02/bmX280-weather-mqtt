#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

//vars
extern WiFiClient espClient;
extern PubSubClient client;

#ifndef INCLUDE_ONCE
#define INCLUDE_ONCE

struct data_bmp280
{
    float temp;
    float pressure;
};

#endif

#define battery_pin 32
// WiFi
#define CONFIG_WIFI_SSID "1337-TPLINK"
#define CONFIG_WIFI_PASS "HIDDEN"

// MQTT
#define CONFIG_MQTT_HOST "192.168.178.54"
#define CONFIG_MQTT_PORT 1883 // Usually 1883
#define CONFIG_MQTT_USER "mqtt"
#define CONFIG_MQTT_PASS "hamqttsecure123"
#define CONFIG_MQTT_CLIENT_ID "esp_temp_balkon" // Must be unique on the MQTT network
#define CONFIG_MQTT_TOPIC_STATE "home/esp_temp_balkon"
