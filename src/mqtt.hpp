
#include "global.h"

namespace mqtt
{
    void callback(char* topic, byte* payload, unsigned int length) {
        Serial.print("Message arrived [");
        Serial.print(topic);
        Serial.print("] ");
        for (int i=0;i<length;i++) {
        Serial.print((char)payload[i]);
        }
        Serial.println();
    }

    void send_state(data_bmp280 data,float battery_voltage)
    {
        DynamicJsonDocument root(100);

        root["temp"] = data.temp;
        root["pressure"] = data.pressure;
        root["battery_voltage"] = battery_voltage;

        char buffer[measureJson(root) + 1];
        serializeJson(root, buffer, sizeof(buffer));
        client.publish(CONFIG_MQTT_TOPIC_STATE, buffer, true);
        Serial.println("[MQTT] Sent update to MQTT Server!");
    }

    void connect()
    {
        client.setCallback(callback);
        client.setServer(CONFIG_MQTT_HOST, CONFIG_MQTT_PORT);
        client.connect(CONFIG_MQTT_CLIENT_ID,CONFIG_MQTT_USER,CONFIG_MQTT_PASS);
        Serial.println("[MQTT] Connection should be good!");
    }

    void disconnect()
    {
        client.disconnect();
        Serial.println("[MQTT] Connection closed!");
    }

} // namespace mqtt

namespace wifi_connection
{
    void setup_wifi()
    {
        Serial.println("[WIFI] connecting to " + String(CONFIG_WIFI_SSID));

        WiFi.mode(WIFI_STA);
        WiFi.begin(CONFIG_WIFI_SSID, CONFIG_WIFI_PASS);

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }

        Serial.println("");
        Serial.println("[WIFI] WiFi connected [" + String(WiFi.localIP()) + "]");
    }

    void disconnect() 
    {
        WiFi.disconnect();
        Serial.println("[WIFI] WiFi disonnected!");
    }
} // namespace wifi_connection