// config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// WiFi Credentials
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;

// Device Configuration
extern const char* DEVICE_ID;

// Pin Definitions
#define FSR_PIN A0
#define MQ135_PIN D5
#define BUZZER_PIN D6
#define VIBRATION_PIN D7
#define SDA_PIN D2
#define SCL_PIN D1

// Display Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// FSR Detection Parameters
extern const int FSR_THRESHOLD;
extern const int FSR_RELEASE_THRESHOLD;
extern const unsigned long MIN_PUFF_DURATION;
extern const unsigned long MAX_PUFF_DURATION;
extern const unsigned long PUFF_COOLDOWN;

// FSR Calibration
extern const int BASELINE_SAMPLES;

// Sensor Configuration
extern const unsigned long SENSOR_READ_INTERVAL;

// NTP Configuration
extern const long TIMEZONE_OFFSET;

// EEPROM Addresses
#define EEPROM_SIZE 512
#define ADDR_TOTAL_PUFFS 0
#define ADDR_MAX_PUFFS 4
#define ADDR_DAILY_PUFFS 8
#define ADDR_REMINDERS 12
#define ADDR_BASELINE 200
#define ADDR_USAGE_HISTORY 250
#define ADDR_REMINDER_COUNT 400

// Device Finding
extern const unsigned long FIND_MODE_DURATION;

// Global Variables (extern declarations)
extern int totalPuffs;
extern int maxPuffsPerInhaler;
extern int dailyPuffs;
extern int lastResetDay;
extern String deviceIP;
extern float currentTemp;
extern float currentHumidity;
extern int currentAQ;
extern float currentPressure;
extern bool findModeActive;
extern unsigned long findModeStartTime;
extern int fsrBaseline;

#endif