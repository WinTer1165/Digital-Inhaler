// sensors.h
#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

void initializeSensors();
void readSensors();
float getTemperature();
float getHumidity();
float getPressure();
int getAirQuality();

#endif