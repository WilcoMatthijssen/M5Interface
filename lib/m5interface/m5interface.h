#pragma once

#include <Arduino.h>
#include <M5EPD.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Free_Fonts.h>


class M5Interface{
    M5EPD_Canvas canvas;
    DynamicJsonDocument doc;
public:
    M5Interface(M5EPD_Driver *driver);
    void begin(const char* ssid, const char*  password, const char* weather_api_key, const char* location);

private:
    void activate_sleep();
    void connect_WiFi(const char* ssid, const char*  password);
    JsonObject get_weather_data(const char* weather_api_key, const char* location);
    
    void draw_date(const int& x, const int& y);
    void draw_battery(const int& x, const int& y);
    void draw_weather_image(int x, int y, String weather);
    void draw(JsonObject& json);
};
