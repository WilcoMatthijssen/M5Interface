#pragma once

#include <Arduino.h>
#include <M5EPD.h>
#include "secrets.h"
#include <ArduinoJson.h>

#include <Free_Fonts.h>
class M5Interface{
    M5EPD_Canvas *_canvas;
public:
    M5Interface(M5EPD_Canvas  *canvas){ _canvas = canvas; }

    
    void draw_date(const int& x, const int& y){
        rtc_date_t date;
        M5.RTC.getDate(&date);

        _canvas->drawString(String(date.day)+ "/" + String(date.mon) + "/" + String(date.year), x, y);

    }

    void draw_battery(const int& x, const int& y){
        float dirty_percentage = (float)(M5.getBatteryVoltage() - 3300) / (float)(4350 - 3300);
        const int percentage = constrain(dirty_percentage * 100, 0, 100);

        _canvas->drawString( String(percentage) + "%", x, y);
    }


    void draw_weather_image(int x, int y, String weather){
        // I should be checking if the file even exists but the drawPngFile function does it for me to some extent.
 
        String filename = "/" + weather + ".png";
        _canvas->drawPngFile(SD, filename.c_str(), x, y,0,0,65,0,1.3);
    }


    void draw(JsonObject& json){
        _canvas->fillRect(0, 0, 540, 60, _canvas->G15);
        _canvas->fillRect(5, 5, 530, 50, _canvas->G0);



        _canvas->setTextSize(1);
        _canvas->setFreeFont(FF20);

        draw_weather_image(0, 60, json["image"].as<String>());
  
        draw_battery(400, 10);
        draw_date(100, 10);



        _canvas->setFreeFont(FF32);

        _canvas->drawString("Neerslagkans: " + json["d0neerslag"].as<String>() + "%", 10, 700);
        _canvas->drawString("Temperatuur: " + json["temp"].as<String>() + "C\n", 10, 750);

        _canvas->setFreeFont(FF19);
        _canvas->setCursor(0, 800);
        _canvas->println(json["verw"].as<String>());
        _canvas->setTextSize(4);

    }
};
