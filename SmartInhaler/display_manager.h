#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Arduino.h>  

void initializeDisplay();
void updateDisplay();
void showBootScreen();
void showWiFiConnecting(const char* ssid, int attempts);
void showWiFiConnected(const String& ip);

#endif