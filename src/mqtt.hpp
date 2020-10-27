
#include "global.h"

namespace mqtt
{
    void callback(char* topic, byte* payload, unsigned int length) {
        Serial.println("Message arrived!");
    }

    void send_state(data_struct data)
    {
        DynamicJsonDocument root(100);

        root["temp"] = data.temp;
        root["pressure"] = data.pressure;

        #ifdef SENSOR_BME280
        root["humidity"] = data.humidity;
        #endif

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
    /*
    ESP32 seems to have problems connecting to the WiFi sometimes, this is a band-aid fix...
    https://github.com/espressif/arduino-esp32/issues/2501#issuecomment-706765775
    */
    
    SemaphoreHandle_t _connected;
    void onEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
        switch (event) {
        case SYSTEM_EVENT_STA_DISCONNECTED:
            xSemaphoreTake(_connected, 0);
            switch (info.disconnected.reason) {
            case WIFI_REASON_NOT_AUTHED:
            case WIFI_REASON_AUTH_FAIL:
                WiFi.reconnect();
                break;
            }
            break;
        case SYSTEM_EVENT_STA_GOT_IP:
        case SYSTEM_EVENT_AP_STACONNECTED:
            xSemaphoreGive(_connected);
            break;
        }
    }

    void setup_wifi()
    {
        Serial.println("[WIFI] connecting to " + String(CONFIG_WIFI_SSID));

        WiFi.mode(WIFI_STA);
        WiFi.setHostname(CONFIG_WIFI_HOST);
        WiFi.begin(CONFIG_WIFI_SSID, CONFIG_WIFI_PASS);

        _connected = xSemaphoreCreateBinary();
        auto on_event_id = WiFi.onEvent(onEvent);

        // Connect to access point. Allow up to 10s for the connection to complete
        WiFi.begin(CONFIG_WIFI_SSID, CONFIG_WIFI_PASS);
        if (xSemaphoreTake(_connected, 10000)) {
        Serial.printf("Connected: %s\n", WiFi.localIP().toString().c_str());
        }  else {
            Serial.printf("Timed out waiting for connection\n");
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