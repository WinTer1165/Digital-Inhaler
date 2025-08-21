// reminder_system.h
#ifndef REMINDER_SYSTEM_H
#define REMINDER_SYSTEM_H

#include <ArduinoJson.h>

struct Reminder
{
    bool active;
    int hour;
    int minute;
    char label[30];
};

void initializeReminderSystem();
void checkReminders();
void setReminder(int index, int hour, int minute, const char *label);
void deleteReminder(int index);
void addRemindersToJson(JsonArray &array);

extern Reminder reminders[5];
extern int reminderCount;

#endif