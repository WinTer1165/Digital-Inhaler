// puff_detector.cpp
#include "puff_detector.h"
#include "config.h"
#include "hardware.h"
#include "storage_manager.h"
#include "websocket_handler.h"
#include <Arduino.h>
#include <EEPROM.h>
#include <RTClib.h>

bool isPuffing = false;
unsigned long puffStartTime = 0;
unsigned long lastPuffTime = 0;
int fsrBaseline = 0;

extern RTC_DS3231 rtc;
extern struct DailyUsage usageHistory[];

void initializePuffDetector()
{
    calibrateFSR();
}

void calibrateFSR()
{
    Serial.println("Calibrating FSR sensor...");
    long sum = 0;

    for (int i = 0; i < BASELINE_SAMPLES; i++)
    {
        sum += analogRead(FSR_PIN);
        delay(50);
    }

    fsrBaseline = sum / BASELINE_SAMPLES;
    Serial.print("FSR Baseline: ");
    Serial.println(fsrBaseline);

    // Store baseline in EEPROM
    EEPROM.put(ADDR_BASELINE, fsrBaseline);
    EEPROM.commit();
}

void handleValidPuff()
{
    totalPuffs++;
    dailyPuffs++;
    lastPuffTime = millis();

    Serial.println("==== VALID PUFF DETECTED ====");
    Serial.print("Total puffs: ");
    Serial.println(totalPuffs);
    Serial.print("Daily puffs: ");
    Serial.println(dailyPuffs);
    Serial.println("=============================");

    // Update today's usage in history
    DateTime now = rtc.now();
    usageHistory[6].puffs = dailyPuffs;

    // Save to EEPROM
    savePuffData();

    // Haptic and audio feedback
    providePuffFeedback();

    // Send WebSocket notification
    sendPuffNotification();

    // Check if max puffs reached
    if (totalPuffs >= maxPuffsPerInhaler)
    {
        sendMaxPuffsAlert();

        // Extended alert
        for (int i = 0; i < 10; i++)
        {
            digitalWrite(BUZZER_PIN, HIGH);
            digitalWrite(VIBRATION_PIN, HIGH);
            delay(200);
            digitalWrite(BUZZER_PIN, LOW);
            digitalWrite(VIBRATION_PIN, LOW);
            delay(200);
        }
    }
}

void detectPuff()
{
    int fsrReading = analogRead(FSR_PIN);

    // Check if puff started
    if (!isPuffing && fsrReading > FSR_THRESHOLD &&
        millis() - lastPuffTime > PUFF_COOLDOWN)
    {
        isPuffing = true;
        puffStartTime = millis();
        Serial.println("==> Puff detection started");
    }

    // Check if puff ended
    if (isPuffing && fsrReading < FSR_RELEASE_THRESHOLD)
    {
        unsigned long puffDuration = millis() - puffStartTime;

        Serial.print("Puff ended. Duration: ");
        Serial.print(puffDuration);
        Serial.println(" ms");

        if (puffDuration >= MIN_PUFF_DURATION && puffDuration <= MAX_PUFF_DURATION)
        {
            handleValidPuff();
        }
        else
        {
            Serial.println("Invalid puff duration - ignored");
        }

        isPuffing = false;
    }

    // Timeout check
    if (isPuffing && millis() - puffStartTime > MAX_PUFF_DURATION)
    {
        Serial.println("Puff timeout - resetting");
        isPuffing = false;
    }
}