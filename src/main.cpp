#include <Arduino.h>

#include "global.h"
#include "deepsleep.hpp"
#include "mqtt.hpp"
#include "temp_sensor.hpp"

#define touch_sens 40 //more = more sens

void setup() 
{
  delay(10);
  Serial.begin(115200);
 
  //Connect
  temp_sensor::setup();
  wifi_connection::setup_wifi();
  delay(500);
  mqtt::connect();

  data_bmp280 data = temp_sensor::get_data();
  float battery_voltage = battery_sensor::get_voltage();
  mqtt::send_state(data,battery_voltage);

  delay(4000);

  //Disconnect
  mqtt::disconnect();
  wifi_connection::disconnect();

  //Sleep so we consume less Power...
  //deepsleep::touchpad_mode(T3,touch_sens);
  //deepsleep::sleep_minutes(10);
}

void loop() 
{
  client.loop();
}


