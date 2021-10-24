#include <Arduino.h>
#include <Wire.h>

#include <M5EPD.h>
#include <WiFi.h>
#include "navbar.h"
#include "secrets.h"

M5EPD_Canvas canvas(&M5.EPD);

NavBar nv;

void setup(){
    M5.begin();
    M5.EPD.SetRotation(90);
    M5.EPD.Clear(true);
    M5.RTC.begin();
    canvas.createCanvas(540, 960);

    canvas.setTextSize(4);
    
}
// #include <Free_Fonts.h>
void loop(){
     
    canvas.fillCanvas(0);

    // canvas.setFreeFont(FM9);

    canvas.drawString("Hello World", 45, 350);
    nv.draw(canvas);

    
    canvas.pushCanvas(0,0,UPDATE_MODE_GC16);
    delay(10000);
}