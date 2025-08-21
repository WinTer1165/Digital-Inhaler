// display_manager.cpp
#include "display_manager.h"
#include "config.h"
#include "sensors.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>
#include <Wire.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
extern RTC_DS3231 rtc;
extern bool isPuffing;
extern unsigned long lastPuffTime;

void initializeDisplay()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
    }
    else
    {
        Serial.println("OLED initialized");
    }
}

void showBootScreen()
{
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(15, 10);
    display.println("SMART");
    display.setCursor(10, 30);
    display.println("INHALER");
    display.setTextSize(1);
    display.setCursor(35, 50);
    display.println("v1.0");
    display.display();
    delay(2000);
}

void updateDisplay()
{
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    // Line 1: IP Address
    display.setCursor(0, 0);
    display.print("IP: ");
    display.print(deviceIP);

    // Line 2: Separator
    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

    // Line 3: Environmental data
    display.setCursor(0, 14);
    display.print("T:");
    display.print(getTemperature(), 1);
    display.print("C H:");
    display.print((int)getHumidity());
    display.print("% AQ:");

    int aq = getAirQuality();
    if (aq >= 80)
    {
        display.print("Good");
    }
    else if (aq >= 60)
    {
        display.print("Mod");
    }
    else
    {
        display.print("Poor");
    }

    // Line 4: Total Puffs
    display.setCursor(0, 28);
    display.setTextSize(2);
    display.print("Puffs: ");
    display.print(totalPuffs);

    // Line 5: Status or alert
    display.setTextSize(1);
    display.setCursor(0, 48);
    if (isPuffing)
    {
        display.print(">>> PUFFING <<<");
    }
    else if (millis() - lastPuffTime < 3000 && lastPuffTime > 0)
    {
        display.print("PUFF RECORDED!");
    }
    else if (findModeActive)
    {
        display.print("FINDING DEVICE!");
    }
    else
    {
        display.print("Ready");
    }

    // Line 6: Time (24-hour format)
    DateTime now = rtc.now();
    display.setCursor(0, 56);
    char timeStr[20];
    sprintf(timeStr, "%02d:%02d:%02d  %02d/%02d",
            now.hour(), now.minute(), now.second(),
            now.day(), now.month());
    display.print(timeStr);

    display.display();
}

void showWiFiConnecting(const char *ssid, int attempts)
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Connecting to WiFi");
    display.print("SSID: ");
    display.println(ssid);
    display.setCursor(0, 30);
    for (int i = 0; i < attempts % 4; i++)
    {
        display.print(".");
    }
    display.display();
}

void showWiFiConnected(const String &ip)
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 20);
    display.println("WiFi Connected!");
    display.setCursor(0, 35);
    display.print("IP: ");
    display.println(ip);
    display.display();
    delay(2000);
}
