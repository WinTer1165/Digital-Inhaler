// hardware.cpp
#include "hardware.h"
#include "config.h"
#include <Arduino.h>

bool findModeActive = false;
unsigned long findModeStartTime = 0;

void initializeHardware()
{
    pinMode(FSR_PIN, INPUT);
    pinMode(MQ135_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(VIBRATION_PIN, OUTPUT);

    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(VIBRATION_PIN, LOW);
}

void testHardware()
{
    Serial.println("Testing Buzzer...");
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);

    Serial.println("Testing Vibration Motor...");
    digitalWrite(VIBRATION_PIN, HIGH);
    delay(200);
    digitalWrite(VIBRATION_PIN, LOW);
    delay(200);

    Serial.println("Hardware test complete!");
}

void providePuffFeedback()
{
    // Two short vibrations
    digitalWrite(VIBRATION_PIN, HIGH);
    delay(100);
    digitalWrite(VIBRATION_PIN, LOW);
    delay(50);
    digitalWrite(VIBRATION_PIN, HIGH);
    delay(100);
    digitalWrite(VIBRATION_PIN, LOW);

    // Short beep
    digitalWrite(BUZZER_PIN, HIGH);
    delay(50);
    digitalWrite(BUZZER_PIN, LOW);
}

void handleFindMode()
{
    if (findModeActive && millis() - findModeStartTime > FIND_MODE_DURATION)
    {
        findModeActive = false;
        digitalWrite(BUZZER_PIN, LOW);
        digitalWrite(VIBRATION_PIN, LOW);
        Serial.println("Find mode ended");
    }

    if (findModeActive)
    {
        static unsigned long lastBeep = 0;
        if (millis() - lastBeep > 500)
        {
            digitalWrite(BUZZER_PIN, !digitalRead(BUZZER_PIN));
            digitalWrite(VIBRATION_PIN, !digitalRead(VIBRATION_PIN));
            lastBeep = millis();
        }
    }
}