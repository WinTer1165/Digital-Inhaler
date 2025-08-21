// storage_manager.cpp
#include "storage_manager.h"
#include "config.h"
#include "reminder_system.h"
#include <EEPROM.h>
#include <RTClib.h>

DailyUsage usageHistory[7];
int totalPuffs = 0;
int maxPuffsPerInhaler = 200;
int dailyPuffs = 0;
int lastResetDay = 0;

extern RTC_DS3231 rtc;
extern int fsrBaseline;

void initializeStorage()
{
    EEPROM.begin(EEPROM_SIZE);
}

void loadAllSettings()
{
    EEPROM.get(ADDR_TOTAL_PUFFS, totalPuffs);
    EEPROM.get(ADDR_MAX_PUFFS, maxPuffsPerInhaler);
    EEPROM.get(ADDR_DAILY_PUFFS, dailyPuffs);
    EEPROM.get(ADDR_BASELINE, fsrBaseline);
    EEPROM.get(ADDR_REMINDER_COUNT, reminderCount);

    // Validate loaded values
    if (totalPuffs < 0 || totalPuffs > 10000)
        totalPuffs = 0;
    if (maxPuffsPerInhaler < 50 || maxPuffsPerInhaler > 500)
        maxPuffsPerInhaler = 200;
    if (dailyPuffs < 0 || dailyPuffs > 500)
        dailyPuffs = 0;
    if (fsrBaseline < 0 || fsrBaseline > 1024)
        fsrBaseline = 0;
    if (reminderCount < 0 || reminderCount > 5)
        reminderCount = 0;

    loadReminders();

    Serial.println("Settings loaded from EEPROM");
    Serial.print("Total Puffs: ");
    Serial.println(totalPuffs);
    Serial.print("Daily Puffs: ");
    Serial.println(dailyPuffs);
    Serial.print("Max Puffs: ");
    Serial.println(maxPuffsPerInhaler);
    Serial.print("Reminders: ");
    Serial.println(reminderCount);
}

void savePuffData()
{
    EEPROM.put(ADDR_TOTAL_PUFFS, totalPuffs);
    EEPROM.put(ADDR_DAILY_PUFFS, dailyPuffs);
    EEPROM.put(ADDR_USAGE_HISTORY, usageHistory);
    EEPROM.commit();
}

void saveReminders()
{
    EEPROM.put(ADDR_REMINDERS, reminders);
    EEPROM.put(ADDR_REMINDER_COUNT, reminderCount);
    EEPROM.commit();
}

void loadReminders()
{
    EEPROM.get(ADDR_REMINDERS, reminders);

    // Validate reminders
    for (int i = 0; i < reminderCount; i++)
    {
        if (reminders[i].hour < 0 || reminders[i].hour >= 24 ||
            reminders[i].minute < 0 || reminders[i].minute >= 60)
        {
            reminders[i].active = false;
        }
    }
}

void setMaxPuffs(int maxPuffs)
{
    maxPuffsPerInhaler = maxPuffs;
    EEPROM.put(ADDR_MAX_PUFFS, maxPuffsPerInhaler);
    EEPROM.commit();
    Serial.print("Max puffs set to: ");
    Serial.println(maxPuffsPerInhaler);
}

void resetPuffCounters()
{
    totalPuffs = 0;
    dailyPuffs = 0;
    EEPROM.put(ADDR_TOTAL_PUFFS, totalPuffs);
    EEPROM.put(ADDR_DAILY_PUFFS, dailyPuffs);
    EEPROM.commit();
    Serial.println("Puff counters reset");
}

void initializeUsageHistory()
{
    // Loading history from EEPROM
    EEPROM.get(ADDR_USAGE_HISTORY, usageHistory);

    // Validate and initialize if needed
    DateTime now = rtc.now();
    bool needsInit = false;

    for (int i = 0; i < 7; i++)
    {
        if (usageHistory[i].month < 1 || usageHistory[i].month > 12 ||
            usageHistory[i].day < 1 || usageHistory[i].day > 31 ||
            usageHistory[i].puffs < 0 || usageHistory[i].puffs > 500)
        {
            needsInit = true;
            break;
        }
    }

    if (needsInit)
    {
        Serial.println("Initializing usage history");
        for (int i = 6; i >= 0; i--)
        {
            DateTime date = DateTime(now.unixtime() - ((6 - i) * 86400));
            usageHistory[i].day = date.day();
            usageHistory[i].month = date.month();
            usageHistory[i].puffs = (i == 6) ? dailyPuffs : 0;
        }

        EEPROM.put(ADDR_USAGE_HISTORY, usageHistory);
        EEPROM.commit();
    }
}

void checkDailyReset()
{
    DateTime now = rtc.now();
    if (now.day() != lastResetDay)
    {
        // Shift history array
        for (int i = 0; i < 6; i++)
        {
            usageHistory[i] = usageHistory[i + 1];
        }

        // Add today as new entry
        usageHistory[6].day = now.day();
        usageHistory[6].month = now.month();
        usageHistory[6].puffs = 0;

        dailyPuffs = 0;
        lastResetDay = now.day();

        EEPROM.put(ADDR_DAILY_PUFFS, dailyPuffs);
        EEPROM.put(ADDR_USAGE_HISTORY, usageHistory);
        EEPROM.commit();

        Serial.println("Daily puff count reset");
    }
}

void addUsageHistoryToJson(JsonArray &array)
{
    for (int i = 0; i < 7; i++)
    {
        JsonObject day = array.createNestedObject();
        day["day"] = usageHistory[i].day;
        day["month"] = usageHistory[i].month;
        day["puffs"] = usageHistory[i].puffs;
    }
}