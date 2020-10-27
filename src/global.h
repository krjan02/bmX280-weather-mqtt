#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

/*
Specify your Sensor Type here...
Please make sure that you have the Adafruit Libary installed for 
the particular sensor you choose

https://github.com/krjan02/bmX280-weather-mqtt#sensor
*/

#define SENSOR_BME280
//#define SENSOR_BMP280

// WiFi
#define CONFIG_WIFI_HOST "mqtt-weather"
#define CONFIG_WIFI_SSID "XXX"
#define CONFIG_WIFI_PASS "XXX"

// MQTT
#define CONFIG_MQTT_HOST "192.168.XXX.XX"
#define CONFIG_MQTT_PORT 1883 // Usually 1883
#define CONFIG_MQTT_USER "XXX"
#define CONFIG_MQTT_PASS "XXX"
#define CONFIG_MQTT_CLIENT_ID "esp_temp_room1" // Must be unique on the MQTT network
#define CONFIG_MQTT_TOPIC_STATE "home/esp_temp_room1" 

/* No changes required (if you are an normal user) */
extern WiFiClient espClient;
extern PubSubClient client;

#ifndef INCLUDE_ONCE
#define INCLUDE_ONCE

struct data_bmp280
{
    float temp;
    float pressure;
};

struct data_bme280
{
    float temp;
    float pressure;
    float humidity;
};

#ifdef SENSOR_BME280
#define data_struct data_bme280
#elif defined(SENSOR_BMP280) 
#define data_struct data_bmp280
#endif

#endif