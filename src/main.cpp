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



// #include "m5interface.h"
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
    // sleep for half an hour
    // inside loop to prevent skipping sleep when powered from usb
    M5.shutdown(1800);
    }