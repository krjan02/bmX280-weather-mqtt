
namespace deepsleep
{
    #define uS_TO_S_FACTOR 1000000
    #define uS_TO_m_FACTOR 60000000

    void start_sleep() {
        Serial.flush(); 
        esp_deep_sleep_start();
    }

    void callback() 
    {
    }

    void touchpad_mode(uint8_t pin,uint16_t threshold) {
          esp_sleep_enable_touchpad_wakeup();
          touchAttachInterrupt(pin,callback,threshold);
    }

    void sleep_seconds(int time)
    {
        esp_sleep_enable_timer_wakeup(time * uS_TO_S_FACTOR);
        start_sleep();
    }

    void sleep_minutes(int time)
    {
        esp_sleep_enable_timer_wakeup(time * uS_TO_m_FACTOR);
        start_sleep();
    }
} // namespace deepsleep
