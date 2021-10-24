#include <Arduino.h>
#include <Wire.h>

#include <M5EPD.h>
#include <WiFi.h>
#include "navbar.h"
#include "secrets.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>

M5EPD_Canvas canvas(&M5.EPD);
	
HTTPClient http;
M5Interface nv(&canvas);

void setup(){
    M5.begin();
    M5.EPD.SetRotation(90);
    M5.EPD.Clear(true);
    M5.RTC.begin();
    canvas.createCanvas(540, 960);

    canvas.setTextSize(4);

    // WiFi.begin(SSID, PASSWORD);
    // while (WiFi.status() != WL_CONNECTED) {
    // delay(500);
    //     Serial.print(".");
    // }
    // Serial.print("WiFi connected with IP: ");
    // Serial.println(WiFi.localIP());

    // http.useHTTP10(true);
    // String request = "https://weerlive.nl/api/json-data-10min.php?key=" + String( WEATHER_API_KEY ) + "&locatie="+ String(LOCATION);
    // http.begin(request);
    // http.GET();

    // DynamicJsonDocument doc(2048);
    // deserializeJson(doc, http.getStream());

    
    // // Disconnect
    // http.end();
    // String output;
    // serializeJson(doc, output);
    // Serial.println(output);
    
}
// #include <Free_Fonts.h>
void loop(){

    canvas.fillCanvas(0);

  
    // canvas.drawPngUrl("http://upload.wikimedia.org/wikipedia/commons/thumb/f/f0/Weather_Icons_-_bkn.svg/240px-Weather_Icons_-_bkn.svg.png", 300 ,300);

    // canvas.drawPngFile(SD, "/Weather.png", 300, 300);


    
    nv.draw();

    
    canvas.pushCanvas(0,0,UPDATE_MODE_GC16);
    
    delay(10000);

}