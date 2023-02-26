#include <Arduino.h>
#include "board_pin.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <ESPmDNS.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

#include "view.h"
#include "rfid.h"


//Wifi Soft AP parameters
const char *wifi_ap_ssid     = "Coffee_Badge";
const char *wifi_ap_password = "coffee_password";
IPAddress IP = {192, 168, 1, 1};
IPAddress gateway = {192, 168, 1, 1};
IPAddress NMask = {255, 255, 255, 0};

//mDNS parameters
const char *mdns_name = "coffee";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String ledState;
String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    ledState = "OFF";
    Serial.print(ledState);
    return ledState;
  }
  return String();
}



void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("Coffeeeee Badge");

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    delay(1000);
    return;
  }
  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while(file){
 
      Serial.print("FILE: ");
      Serial.println(file.name());
 
      file = root.openNextFile();
  }

  setup_gfx();

  WiFi.mode(WIFI_AP);
  WiFi.softAP(wifi_ap_ssid, wifi_ap_password);

  delay(1000);

  WiFi.softAPConfig(IP, gateway, NMask);

  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);

  if(!MDNS.begin(mdns_name)) {
     Serial.println("Error starting mDNS");
     return;
  }


  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // Route to set GPIO to HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    // digitalWrite(ledPin, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to set GPIO to LOW
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    // digitalWrite(ledPin, LOW);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Start server
  server.begin();


  delay(3000);
  RFID_setup();
}

void loop() {
  RFID_loop();

}