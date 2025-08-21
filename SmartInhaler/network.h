// network.h
#ifndef NETWORK_H
#define NETWORK_H

#include <Arduino.h>
#include <ESP8266WebServer.h>


void connectToWiFi();
void setupWebServer();
void handleWebServer();
String getDeviceIP();

extern ESP8266WebServer server;

#endif