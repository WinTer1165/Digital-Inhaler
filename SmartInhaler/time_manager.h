// time_manager.h
#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <Arduino.h>

void initializeTimeManager();
void syncTimeFromNTP();
void setTimeFromCompilation();
void updateTimeFromNTP();

#endif
