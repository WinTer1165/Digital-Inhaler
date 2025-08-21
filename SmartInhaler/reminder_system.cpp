// reminder_system.cpp
#include "reminder_system.h"
#include "config.h"
#include "storage_manager.h"
#include "websocket_handler.h"
#include <RTClib.h>
#include <Arduino.h>

Reminder reminders[5];
int reminderCount = 0;
int lastCheckedMinute = -1;

extern RTC_DS3231 rtc;

void initializeReminderSystem()
{
    loadReminders();

    Serial.println("=== Loaded Reminders ===");
    for (int i = 0; i < reminderCount; i++)
    {
        if (reminders[i].active)
        {
            Serial.printf("Reminder %d: %02d:%02d - %s\n",
                          i, reminders[i].hour, reminders[i].minute, reminders[i].label);
        }
    }
    Serial.println("========================");
}

void checkReminders()
{
    DateTime now = rtc.now();

    if (now.minute() != lastCheckedMinute)
    {
        lastCheckedMinute = now.minute();

        Serial.printf("[Reminder Check] Time: %02d:%02d, Active reminders: %d\n",
                      now.hour(), now.minute(), reminderCount);

        for (int i = 0; i < reminderCount; i++)
        {
            if (reminders[i].active)
            {
                Serial.printf("  Checking reminder %d: %02d:%02d\n",
                              i, reminders[i].hour, reminders[i].minute);

                if (now.hour() == reminders[i].hour &&
                    now.minute() == reminders[i].minute)
                {

                    Serial.print(">>> REMINDER TRIGGERED: ");
                    Serial.println(reminders[i].label);

                    for (int j = 0; j < 5; j++)
                    {
                        digitalWrite(BUZZER_PIN, HIGH);
                        digitalWrite(VIBRATION_PIN, HIGH);
                        delay(300);

                        digitalWrite(BUZZER_PIN, LOW);
                        digitalWrite(VIBRATION_PIN, LOW);
                        delay(200);
                    }

                    // Send WebSocket notification
                    StaticJsonDocument<256> doc;
                    doc["type"] = "reminder";
                    doc["label"] = reminders[i].label;

                    String output;
                    serializeJson(doc, output);
                    webSocket.broadcastTXT(output);

                    break; // Only trigger one reminder per minute
                }
            }
        }
    }
}

void setReminder(int index, int hour, int minute, const char *label)
{
    if (index < 5)
    {
        reminders[index].active = true;
        reminders[index].hour = hour;
        reminders[index].minute = minute;
        strcpy(reminders[index].label, label);

        if (index >= reminderCount)
        {
            reminderCount = index + 1;
        }

        saveReminders();
        Serial.println("Reminder set successfully");
    }
}

void deleteReminder(int index)
{
    if (index < reminderCount)
    {
        // Shift reminders down
        for (int i = index; i < reminderCount - 1; i++)
        {
            reminders[i] = reminders[i + 1];
        }
        reminderCount--;
        reminders[reminderCount].active = false;

        saveReminders();
        Serial.println("Reminder deleted");
    }
}

void addRemindersToJson(JsonArray &array)
{
    for (int i = 0; i < reminderCount; i++)
    {
        if (reminders[i].active)
        {
            JsonObject reminder = array.createNestedObject();
            char timeStr[6];
            sprintf(timeStr, "%02d:%02d", reminders[i].hour, reminders[i].minute);
            reminder["time"] = timeStr;
            reminder["label"] = reminders[i].label;
        }
    }
}