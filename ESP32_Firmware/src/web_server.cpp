/**
 * @file web_server.cpp
 * @author David Leval
 * @version 0.1
 * @date 2023-08-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "web_server.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <ESPmDNS.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

#if DEBUG_WEB_SERVER == 1
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTF(x, args...) Serial.printf(x, ##args)
#define DEBUG_WRITE(x) Serial.write(x)
#else
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINT(x)
#define DEBUG_PRINTF(x, args...)
#define DEBUG_WRITE(x)
#endif

// Wifi Soft AP parameters
const char *wifi_ap_ssid = "Coffee_Badge";
const char *wifi_ap_password = "coffeesocomec";
IPAddress IP = {192, 168, 1, 1};
IPAddress gateway = {192, 168, 1, 1};
IPAddress NMask = {255, 255, 255, 0};

// mDNS parameters
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

WEB_SERVER::WEB_SERVER(/* args */)
{
}

WEB_SERVER::~WEB_SERVER()
{
}

void WEB_SERVER::begin(void)
{
    // Initialize SPIFFS
    DEBUG_PRINTLN("Init SPIFFS");
    if (!SPIFFS.begin(true))
    {
        DEBUG_PRINTLN("An Error has occurred while mounting SPIFFS");
        delay(1000);
        return;
    }
    File root = SPIFFS.open("/");
    File file = root.openNextFile();
    while (file)
    {

        DEBUG_PRINT("FILE: ");
        DEBUG_PRINTLN(file.name());

        file = root.openNextFile();
    }

    // Wifi setup
    WiFi.mode(WIFI_AP);
    WiFi.softAP(wifi_ap_ssid, wifi_ap_password);

    delay(1000);

    WiFi.softAPConfig(IP, gateway, NMask);

    IPAddress myIP = WiFi.softAPIP();
    Serial.println(myIP);

    if (!MDNS.begin(mdns_name))
    {
        DEBUG_PRINTLN("Error starting mDNS");
        return;
    }

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", String(), false, processor);
    });

    // Route to load index.html file
    server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", String(), false, processor);
    });
    
    // Route to load style.css file
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/style.css", "text/css");
    });

    // Route to load coffee_db.json file
    server.on("/coffee_db.json", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/coffee_db.json", "text/css");
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
}

WEB_SERVER web_server;
