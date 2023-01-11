#include <Arduino.h>

#include <M5StickCPlus.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

// https://github.com/m5stack/M5StickC-Plus

//Wifi Soft AP parameters
const char *wifi_ap_ssid     = "Coffee_Badge";
const char *wifi_ap_password = "coffee_password";

WiFiServer server(80);

void setup() {
  M5.begin();
  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(wifi_ap_ssid, wifi_ap_password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);

  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {
    Serial.print("New Client:");
    String currentLine = "";  // make a String to hold incoming data from the client.
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();  // store the read a byte. 
        Serial.write(c);
        if (c == '\n') {  // \n is the end of the client'S HTTP request, indicating that the client has sent a new request
          if (currentLine.length() == 0) {
            // Here are the instructions to create a page.
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK) and a content-type so the client
            // knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            String page = "<!DOCTYPE html>";  // Début page HTML
            page += "<head>";
            page += "    <title> Coffee Account Badge</title>";
            page += "    <meta http-equiv='refresh' content='60' name='viewport' content='width=device-width, initial-scale=1' charset='UTF-8'/>";
            page += "</head>";
            page += "<body lang='fr'>";
            page += "    <h1>Serveur</h1>";
            page += "    <p>Ce serveur est hébergé sur un ESP32</p>";
            page += "    <i>Créé par DVI</i>";
            page += "</body>";
            page += "</html>";  // Fin page HTML
            client.print(page);
            client.println(); // The HTTP response ends with another blank line
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        //GET method
        if (currentLine.endsWith("GET /toto")) {
          Serial.println("toto");
        } else if (currentLine.endsWith("GET /titi")) {
          Serial.println("titi");
        }
      }
    }
  }
}