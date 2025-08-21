// network.cpp
#include "network.h"
#include "config.h"
#include "web_interface.h"
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

ESP8266WebServer server(80);
String deviceIP = "0.0.0.0";

void connectToWiFi()
{
    Serial.print("Connecting to WiFi: ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 30)
    {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\nWiFi connected!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        deviceIP = WiFi.localIP().toString();
    }
    else
    {
        Serial.println("\nWiFi connection failed!");
        deviceIP = "Not Connected";
    }
}

void setupWebServer()
{
    server.on("/", HTTP_GET, []()
              { server.send_P(200, "text/html", MAIN_page); });

    server.on("/status", HTTP_GET, []()
              {
    StaticJsonDocument<512> doc;
    doc["connected"] = true;
    doc["deviceId"] = DEVICE_ID;
    doc["totalPuffs"] = totalPuffs;
    doc["dailyPuffs"] = dailyPuffs;
    doc["maxPuffs"] = maxPuffsPerInhaler;
    doc["temperature"] = currentTemp;
    doc["humidity"] = currentHumidity;
    doc["airQuality"] = currentAQ;
    doc["pressure"] = currentPressure;
    doc["ip"] = deviceIP;
    
    String response;
    serializeJson(doc, response);
    server.send(200, "application/json", response); });

    server.begin();
    Serial.println("HTTP server started on port 80");
}

void handleWebServer()
{
    server.handleClient();
}

String getDeviceIP()
{
    return deviceIP;
}