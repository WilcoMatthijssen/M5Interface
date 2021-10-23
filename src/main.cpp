#include <Arduino.h>
#include <Wire.h>
#include <M5EPD.h>
#include <WiFi.h>
M5EPD_Canvas canvas(&M5.EPD);

class Battery{
public:
    int percentage(){
        float dirty_percentage = (float)(M5.getBatteryVoltage() - 3300) / (float)(4350 - 3300);
        return constrain(dirty_percentage * 100, 0, 100);
    }
    void draw(const int& x, const int& y, M5EPD_Canvas& canvas){
        canvas.drawString( String(percentage()) + "%", x, y);
    }
};


class Date{
    
public:
    rtc_date_t dater(){
        rtc_date_t d;
        M5.RTC.getDate(&d);
        return d;
    }

    void draw(const int& x, const int& y, M5EPD_Canvas& canvas){
    
        rtc_date_t d = dater();

        canvas.drawString(String(d.day)+ "/" + String(d.mon) + "/" + String(d.year), x, y);

    }
};



class NavBar{
public:
    Battery battery;
    Date date;

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
    
 
    
  

        battery.draw(400, 10, canvas);
        date.draw(100, 10, canvas);
    }
};



NavBar nv;

void setup()
{
    M5.begin();
    M5.EPD.SetRotation(90);
    M5.EPD.Clear(true);
    M5.RTC.begin();
    canvas.createCanvas(540, 960);

    canvas.setTextSize(3);

}

void loop()
{
     
    canvas.fillCanvas(0);
    canvas.drawString("Hello World", 45, 350);
    nv.draw(canvas);

    
    canvas.pushCanvas(0,0,UPDATE_MODE_GC16);
    delay(1000);
}