#pragma once

#include <Arduino.h>
#include <M5EPD.h>
#include "secrets.h"


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
        _canvas->drawPngFile(SD, filename.c_str(), x, y);
    }


    void draw(){
        _canvas->fillRect(0, 0, 540, 60, _canvas->G15);
        _canvas->fillRect(5, 5, 530, 50, _canvas->G0);

        String weather = "Weather";

        _canvas->setTextSize(1);
        _canvas->setFreeFont(FF20);

        draw_weather_image(40,150,weather);
  
        draw_battery(400, 10);
        draw_date(100, 10);



        _canvas->setFreeFont(FF32);

        _canvas->drawString("Neerslagkans: 40%", 10, 600);
        _canvas->drawString("Temperatuur: 17.5C\n", 10, 650);

        _canvas->setFreeFont(FF19);
        _canvas->setCursor(0, 700);
        _canvas->println("Zonnig, morgen overwegend bewolkt en af en toe regen");
        _canvas->setTextSize(4);
        // _canvas->drawString("Hello World", 45, 105);
        // _canvas->drawString("Neerslagkans: 40%", 45, 700);
        // _canvas->drawString("Temperatuur: 17.5C", 345, 700);
        // _canvas->drawString("Zonnig, morgen overwegend bewolkt en af en toe regen", 45, 750);
    }
};
