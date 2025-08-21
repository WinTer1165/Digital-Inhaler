// time_manager.cpp
#include "time_manager.h"
#include "config.h"
#include "storage_manager.h"
#include <RTClib.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

RTC_DS3231 rtc;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", TIMEZONE_OFFSET, 60000);

void initializeTimeManager()
{
    if (!rtc.begin())
    {
        Serial.println("RTC not found!");
    }
    else
    {
        Serial.println("RTC initialized");

        // Set time from compilation if RTC lost power
        if (rtc.lostPower())
        {
            Serial.println("RTC lost power, setting time from compilation...");
            setTimeFromCompilation();
        }
    }

    // Try to sync time from NTP if WiFi is connected
    if (WiFi.status() == WL_CONNECTED)
    {
        syncTimeFromNTP();
    }
    else
    {
        setTimeFromCompilation();
    }

    // Print current RTC time for debugging
    DateTime now = rtc.now();
    Serial.printf("Current RTC time: %02d:%02d:%02d %02d/%02d/%04d\n",
                  now.hour(), now.minute(), now.second(),
                  now.day(), now.month(), now.year());
}

void setTimeFromCompilation()
{
    const char *date = __DATE__;
    const char *time = __TIME__;

    char month_str[4];
    int day, year, hour, minute, second;

    sscanf(date, "%s %d %d", month_str, &day, &year);
    sscanf(time, "%d:%d:%d", &hour, &minute, &second);

    // Convert month string to number
    int month = 0;
    const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                            "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (int i = 0; i < 12; i++)
    {
        if (strcmp(month_str, months[i]) == 0)
        {
            month = i + 1;
            break;
        }
    }

    rtc.adjust(DateTime(year, month, day, hour, minute, second));

    Serial.println("RTC set from compilation time!");
    Serial.printf("Set to: %02d:%02d:%02d %02d/%02d/%04d\n",
                  hour, minute, second, day, month, year);

    lastResetDay = day;
}

void syncTimeFromNTP()
{
    Serial.println("Syncing time from NTP...");

    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("No WiFi for NTP sync, using compilation time");
        setTimeFromCompilation();
        return;
    }

    timeClient.begin();

    int attempts = 0;
    bool success = false;

    while (!success && attempts < 5)
    {
        success = timeClient.update();
        if (!success)
        {
            timeClient.forceUpdate();
            attempts++;
            delay(1000);
            Serial.print(".");
        }
    }

    if (success && timeClient.isTimeSet())
    {
        unsigned long epochTime = timeClient.getEpochTime();
        rtc.adjust(DateTime(epochTime));

        DateTime now = rtc.now();
        Serial.println("\nRTC synchronized with NTP!");
        Serial.printf("Current time: %02d:%02d:%02d %02d/%02d/%04d\n",
                      now.hour(), now.minute(), now.second(),
                      now.day(), now.month(), now.year());
        lastResetDay = now.day();
    }
    else
    {
        Serial.println("\nNTP sync failed, using compilation time as fallback");
        setTimeFromCompilation();
    }
}

void updateTimeFromNTP()
{
    static unsigned long lastNTPUpdate = 0;
    if (WiFi.status() == WL_CONNECTED && millis() - lastNTPUpdate > 3600000)
    {
        timeClient.update();
        if (timeClient.isTimeSet())
        {
            rtc.adjust(DateTime(timeClient.getEpochTime()));
            Serial.println("RTC re-synchronized with NTP");
        }
        lastNTPUpdate = millis();
    }
}