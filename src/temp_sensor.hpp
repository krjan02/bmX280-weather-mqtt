#include <Adafruit_Sensor.h>
#include "global.h"

#ifdef SENSOR_BME280
#include <Adafruit_BME280.h>
#endif

#ifdef SENSOR_BMP280 
#include <Adafruit_BMP280.h>
#endif

namespace temp_sensor
{
    #ifdef SENSOR_BME280
    Adafruit_BME280 sensor;
    #elif defined(SENSOR_BMP280) 
    Adafruit_BMP280 sensor;
    #endif

    void setup()
    {

        #ifdef SENSOR_BME280
        if (!sensor.begin(0x76))
        {
            Serial.println("[Temp-Sensor] Can't find the BME280 (maybe you f*cked up the wiring?)");
            while (1);
        }
        #elif defined(SENSOR_BMP280) 
        if (!sensor.begin(0x76))
        {
            Serial.println("[Temp-Sensor] Can't find the BMP280 (maybe you f*cked up the wiring?)");
            while (1);
        }
        #endif

        Serial.println("[Temp-Sensor] Sensor successfully attached!");
    }

    data_struct get_data()
    {
        #ifdef SENSOR_BME280
        data_struct data = {sensor.readTemperature(),sensor.readPressure()/100,sensor.readHumidity()};
        #elif defined(SENSOR_BMP280) 
        data_struct data = {sensor.readTemperature(),sensor.readPressure()/100};
        #endif

        Serial.println("temp -> " + String(data.temp));
        return data;
    }
} // namespace temp_sensor
