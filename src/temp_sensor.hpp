#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#include "global.h"

namespace temp_sensor
{
    Adafruit_BMP280 bmp;

    void setup()
    {
        if (!bmp.begin(0x76))
        {
            Serial.println("[Temp-Sensor] Can't find the BMP280 (maybe you f*cked up the wiring?");
            while (1);
        }
        Serial.println("[Temp-Sensor] Sensor successfully attached!");
    }

    data_bmp280 get_data()
    {
        data_bmp280 data = {bmp.readTemperature(),bmp.readPressure()/100};
        Serial.println("[Temp-Sensor] read -> temp: " + String(data.temp) + " pressure: " + String(data.pressure));
        return data;
    }
} // namespace temp_sensor

namespace battery_sensor 
{
    float get_voltage() 
    {
        int adc_value = analogRead(battery_pin);
        float voltage = (adc_value * 3.3 ) / (4095);
        Serial.println("[Battery-Sensor] read -> voltage: " + String(voltage));
        return voltage;
    }
}