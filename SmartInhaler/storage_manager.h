// storage_manager.h
#ifndef STORAGE_MANAGER_H
#define STORAGE_MANAGER_H

#include <ArduinoJson.h>

struct DailyUsage
{
    int day;
    int month;
    int puffs;
};

void initializeStorage();
void loadAllSettings();
void savePuffData();
void saveReminders();
void loadReminders();
void setMaxPuffs(int maxPuffs);
void resetPuffCounters();
void initializeUsageHistory();
void checkDailyReset();
void addUsageHistoryToJson(JsonArray &array);

extern DailyUsage usageHistory[7];
extern int totalPuffs;
extern int maxPuffsPerInhaler;
extern int dailyPuffs;
extern int lastResetDay;

#endif