#include "m5interface.h"


M5Interface::M5Interface(M5EPD_Driver *driver): canvas(driver), doc(2048){  }

void M5Interface::begin(const char* ssid, const char*  password, const char* weather_api_key, const char* location){
    M5.begin();

    connect_WiFi(ssid, password);
    JsonObject weather_data = get_weather_data(weather_api_key, location);

    draw(weather_data);
    delay(500);

    // inside loop to prevent skipping sleep when powered from usb
    while(true){activate_sleep();}
}



void M5Interface::activate_sleep(){
    M5.shutdown(1800);
}

void M5Interface::connect_WiFi(const char* ssid, const char*  password){
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
        Serial.print(".");
    }
    Serial.print("WiFi connected with IP: ");
    Serial.println(WiFi.localIP());
}

JsonObject M5Interface::get_weather_data(const char* weather_api_key, const char* location){
    HTTPClient http;
    http.useHTTP10(true);
    String request = "http://weerlive.nl/api/json-data-10min.php?key=" + String( weather_api_key ) + "&locatie="+ String( location );
    http.begin(request);
    http.GET();

    // DynamicJsonDocument doc(2048);
    deserializeJson(doc, http.getStream());
    http.end();
    return doc["liveweer"][0].as<JsonObject>();
}
    
void M5Interface::draw_date(const int& x, const int& y){
    M5.RTC.begin();
    rtc_date_t date;
    M5.RTC.getDate(&date);

    canvas.drawString(String(date.day)+ "/" + String(date.mon) + "/" + String(date.year), x, y);

}

void M5Interface::draw_battery(const int& x, const int& y){
    // Get average of voltage because of fluctiations in measurements
    const int sample_size = 100;
    int voltage = 0;
    for(int i = 0; i< sample_size; ++i){ voltage += M5.getBatteryVoltage();}
    voltage /= sample_size;

    const int dirty_percentage = map(voltage, 3300, 4350, 0, 100);
    const int percentage = constrain(dirty_percentage * 100, 0, 100);

    canvas.drawString( String(percentage) + "%", x, y);
}


void M5Interface::draw_weather_image(int x, int y, String weather){
    // I should be checking if the file even exists but the drawPngFile function does it for me to some extent.
    String filename = "/" + weather + ".png";
    canvas.drawPngFile(SD, filename.c_str(), x, y,0,0,65,0,1.3);
}


void M5Interface::draw(JsonObject& json){
    M5.EPD.SetRotation(90);
    canvas.createCanvas(540, 960);
    canvas.fillRect(0, 0, 540, 60, canvas.G15);
    canvas.fillRect(5, 5, 530, 50, canvas.G0);

    canvas.setTextSize(1);
    canvas.setFreeFont(FF20);

    draw_weather_image(0, 60, json["image"].as<String>());
    draw_battery(400, 10);
    draw_date(100, 10);


    canvas.setFreeFont(FF32);

    canvas.drawString("Neerslagkans: " + json["d0neerslag"].as<String>() + "%", 10, 700);
    canvas.drawString("Temperatuur: " + json["temp"].as<String>() + "C\n", 10, 750);

    canvas.setFreeFont(FF19);
    canvas.setCursor(0, 800);
    canvas.println(json["verw"].as<String>());
    canvas.setTextSize(4);

    M5.EPD.Clear(true);
    canvas.pushCanvas(0,0,UPDATE_MODE_GC16);

}
