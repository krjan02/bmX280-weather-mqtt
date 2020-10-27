
<h1 align="center">Welcome to BMx280-weather-mqtt 👋</h1>
<p>
</p>

> Using BME280/BMP280 and MQTT on ESP32 to monitor climate

This was made to monitor the weather in  my House/Outside, i used a JSON Payload instead of seperated states for every value.

## Prerequisites

This was made for the ESP32 and it's pretty straightforward to make this run on a ESP8266

**I would suggest using VSCode with PlatformIO**, even thoughyou can use the ArdunioIDE aswell, if you change the file structure

### Libarys

 - [pubsubclient](https://github.com/knolleary/pubsubclient)
 - [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
 - [Adafruit_Sensor](https://github.com/adafruit/Adafruit_Sensor)

Depending on your Sensor:
 - [Adafruit_BME280_Library](https://github.com/adafruit/Adafruit_BME280_Library)
 - [Adafruit_BMP280_Library](https://github.com/adafruit/Adafruit_BMP280_Library)

## Sensor

Since you can use both BME280 or BME280, you can specify your sensor in [global.h](https://github.com/krjan02/bmX280-weather-mqtt/blob/master/src/global.h)

```sh
#define SENSOR_BME280
//#define SENSOR_BMP280
```
This would now expect an BME280 Sensor

That's how you connect the BMx280 to the ESP:
```sh
BMx280 <----> ESP32
 SDA <-----> GPIO21
 SCL <-----> GPIO22
```

## Usage

Enter your WifI and MQTT Settings in [global.h](https://github.com/krjan02/bmX280-weather-mqtt/blob/master/src/global.h) just like this:

```sh
// WiFi
#define CONFIG_WIFI_HOST "mqtt-temp-livingroom"
#define CONFIG_WIFI_SSID "yourssid"
#define CONFIG_WIFI_PASS "yoursupersecretpassword"

// MQTT
#define CONFIG_MQTT_HOST "192.168.0.1"
#define CONFIG_MQTT_PORT 1883 // Usually 1883
#define CONFIG_MQTT_USER "hassio"
#define CONFIG_MQTT_PASS "secret123"
#define CONFIG_MQTT_CLIENT_ID "esp_temp_livingroom1" // Must be unique on the MQTT network
#define CONFIG_MQTT_TOPIC_STATE "home/esp_temp_livingroom" 
```

That's it, you can upload to the ESP!

### HomeAssistant

```json
- platform: mqtt
  name: "Livingroom °C"
  state_topic: "home/esp_temp_livingroom1"
  value_template: "{{ value_json.temp }}"
  unit_of_measurement: "°C"
  force_update: true
  
- platform: mqtt
  name: "Livingroom hPa"
  state_topic: "home/esp_temp_livingroom1"
  value_template: "{{ value_json.pressure }}"
  unit_of_measurement: "hPa"
  force_update: true

- platform: mqtt
  name: "Livingroom Humidity"
  state_topic: "home/esp_temp_livingroom1"
  value_template: "{{ value_json.humidity }}"
  unit_of_measurement: "%"
  force_update: true
```

![Example](https://i.imgur.com/CYI3jn7.png)

## Author

👤 **krjan02**

* Github: [@krjan02](https://github.com/krjan02)

## Show your support

Give a ⭐️ if this project helped you!

***
