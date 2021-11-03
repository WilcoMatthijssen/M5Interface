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
M5Interface weatherdisplay(&canvas);




void setup(){
    M5.begin();
    

    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
        Serial.print(".");
    }
    Serial.print("WiFi connected with IP: ");
    Serial.println(WiFi.localIP());

    http.useHTTP10(true);
    String request = "http://weerlive.nl/api/json-data-10min.php?key=" + String( WEATHER_API_KEY ) + "&locatie="+ String( LOCATION );
    http.begin(request);
    http.GET();

    DynamicJsonDocument doc(2048);
    deserializeJson(doc, http.getStream());
    http.end();
    JsonObject weather_info = doc["liveweer"][0].as<JsonObject>();
    // serializeJson(obj, Serial);


    M5.EPD.SetRotation(90);
    M5.RTC.begin();
    canvas.createCanvas(540, 960);
    weatherdisplay.draw(weather_info);

    // Removes shadow stripes in display
    M5.EPD.Clear(true);

    // Update display with highest quality
    canvas.pushCanvas(0,0,UPDATE_MODE_GC16);
    delay(500);


}

void loop(){
    // sleep for 1 hour
    // inside loop to prevent skipping sleep when powered from usb.
    RTC_Time sleep_time;
    M5.RTC.getTime(&sleep_time);
    sleep_time.hour  = (sleep_time.hour + 1) % 24;
    sleep_time.min   = 0;
    sleep_time.sec   = 0;
    M5.shutdown(sleep_time);
    }