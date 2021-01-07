#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <string>

#include "environment.h"

static const uint8_t PIN_5 = 0;       // pin 5 in diagram
static const uint8_t PIN_7 = 3;       // pin 7 in diagram
static const uint8_t PIN_2 = 1;       // pin 2 in diagram
static const uint8_t PIN_LED = PIN_2; // pin 2 is also associated to the LED (LED is ON when this pin is set to OFF)

ESP8266WiFiMulti wifiController;
ESP8266WebServer server(80);

void handleRoot();
void toggleLED();
void handleNotFound();

void setup(void)
{
  Serial.begin(250000);
  Serial.print("\nESP8266 Module ON, connecting to network");
  wifiController.addAP(SSID, SSID_PASS);

  while (wifiController.run() != WL_CONNECTED)
  { // Wait for the Wi-Fi to connect
    Serial.print('.');
    delay(1000);
  }

  Serial.println("Success!\n");
  Serial.print("Connected to: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266"))
  { // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  }
  else
  {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/", HTTP_GET, handleRoot);
  server.on("/pinStatus", HTTP_GET, handlePinStatus);
  server.on("/toggleLED", HTTP_POST, toggleLED);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  delay(1000); // delay here is needed for serial to finish printing before possibly overriding serial comm ports config
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, 1); // OFF
  pinMode(PIN_5, INPUT);
}

void loop(void)
{
  server.handleClient();
}

void handleRoot()
{
  server.send(200, "text/html", INDEX_HTML);
}

void handlePinStatus()
{
  std::string pinStatus = digitalRead(PIN_LED) != 1 ? "true" : "false";
  std::string response = "{ \"status\": " + pinStatus + " }";
  server.send(200, "application/json; charset=utf-8", response.c_str());
}

void toggleLED()
{
  digitalWrite(PIN_LED, !digitalRead(PIN_LED));
  server.send(200);
}

void handleNotFound()
{
  server.send(404, "text/plain", "404: Not found");
}