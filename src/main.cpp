#include <Arduino.h>
#include "secrets.h"
#include <M5EPD.h>
#include "m5interface.h"

M5Interface weatherdisplay(&M5.EPD);

void setup(){
    weatherdisplay.begin(SSID, PASSWORD, WEATHER_API_KEY, LOCATION);
}

void loop(){}