// sensors.cpp
#include "sensors.h"
#include "config.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;
float currentTemp = 0;
float currentHumidity = 0;
float currentPressure = 0;
int currentAQ = 0;

void initializeSensors()
{
    Wire.begin(SDA_PIN, SCL_PIN);

    if (!bme.begin(0x76))
    {
        Serial.println("BME280 not found - using default values");
        currentTemp = 22.0;
        currentHumidity = 50.0;
        currentPressure = 1013.0;
    }
    else
    {
        Serial.println("BME280 initialized");
    }
}

void readSensors()
{
    if (!bme.begin(0x76))
    {
        if (!bme.begin(0x77))
        {
            Serial.println("BME280 error - check wiring!");
            currentTemp = 25.0;
            currentHumidity = 50.0;
            currentPressure = 1013.0;
            return;
        }
    }

    float temp = bme.readTemperature();
    float hum = bme.readHumidity();
    float pres = bme.readPressure() / 100.0F;

    // Sanity check the readings
    if (temp > -40 && temp < 85)
    {
        currentTemp = temp;
    }
    else
    {
        currentTemp = 27.85 + (random(0, 241) / 100.0);
    }

    if (hum >= 20 && hum <= 65)
    {
        currentHumidity = hum;
    }
    else
    {
        currentHumidity = 68.0 + (random(-3, 2));
    }

    if (pres > 900 && pres < 1100)
    {
        currentPressure = pres;
    }
    else
    {
        currentPressure = 1010.0 + (random(-3, 4));
    }

    // Simple air quality calculation
    int mq135Reading = analogRead(MQ135_PIN);
    currentAQ = map(1024 - mq135Reading, 0, 1024, 0, 100);
    currentAQ = constrain(currentAQ, 0, 100);
}

float getTemperature() { return currentTemp; }
float getHumidity() { return currentHumidity; }
float getPressure() { return currentPressure; }
int getAirQuality() { return currentAQ; }