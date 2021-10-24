#include <Arduino.h>
#include <M5EPD.h>
#include "secrets.h"
class NavBar{
public:
    
    void draw_date(const int& x, const int& y, M5EPD_Canvas& canvas){
        rtc_date_t date;
        M5.RTC.getDate(&date);

        canvas.drawString(String(date.day)+ "/" + String(date.mon) + "/" + String(date.year), x, y);

    }

    void draw_battery(const int& x, const int& y, M5EPD_Canvas& canvas){
        float dirty_percentage = (float)(M5.getBatteryVoltage() - 3300) / (float)(4350 - 3300);
        const int percentage = constrain(dirty_percentage * 100, 0, 100);

        canvas.drawString( String(percentage) + "%", x, y);
    }



    void draw(M5EPD_Canvas& canvas){
        canvas.fillRect(0, 0, 540, 100, 15);
        canvas.fillRect(5, 5, 530, 90, 0);


        canvas.fillRect(0, 0, 540, 100, 15);
        canvas.fillRect(0, 100, 540, 100, 13);
        canvas.fillRect(0, 200, 540, 100, 11);
        canvas.fillRect(0, 300, 540, 100, 9);
        canvas.fillRect(0, 400, 540, 100, 7);
        canvas.fillRect(0, 500, 540, 100, 5);
        canvas.fillRect(0, 600, 540, 100, 3);
        canvas.fillRect(0, 700, 540, 100, 1);
        canvas.fillRect(0, 800, 540, 100, 0);
    
        
    
  
        draw_battery(400, 10, canvas);
        draw_date(100, 10, canvas);
    }
};
