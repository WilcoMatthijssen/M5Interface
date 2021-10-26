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

    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
        Serial.print(".");
    }
    Serial.print("WiFi connected with IP: ");
    Serial.println(WiFi.localIP());

    http.useHTTP10(true);
    String request = "http://weerlive.nl/api/json-data-10min.php?key=" + String( WEATHER_API_KEY ) + "&locatie="+ String(LOCATION);
    http.begin(request);
    http.GET();

    DynamicJsonDocument doc(2048);
    deserializeJson(doc, http.getStream());
    http.end();
 

    JsonObject obj = doc["liveweer"][0].as<JsonObject>();
    // serializeJson(obj, Serial);


    canvas.fillCanvas(0);
    nv.draw(obj);
    canvas.pushCanvas(0,0,UPDATE_MODE_GC16);
    delay(500);
    
    RTC_Time sleep_time;
    M5.RTC.getTime(&sleep_time);
    sleep_time.hour += 1;
    sleep_time.min   = 0;
    sleep_time.sec   = 0;

    M5.shutdown(sleep_time);

}

void loop(){}