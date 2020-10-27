#include <Arduino.h>

#include "global.h"
#include "deepsleep.hpp"
#include "mqtt.hpp"
#include "temp_sensor.hpp"

void setup() 
{
  delay(1000);

  Serial.begin(115200);
 
  //Connect
  temp_sensor::setup();
  wifi_connection::setup_wifi();
  delay(500);
  mqtt::connect();

  data_struct data = temp_sensor::get_data();
  mqtt::send_state(data);

  delay(1000);

  //Disconnect
  mqtt::disconnect();
  wifi_connection::disconnect();

  //Sleep so we consume less Power...
  deepsleep::sleep_seconds(60);
}

void loop() 
{
  client.loop();
}


