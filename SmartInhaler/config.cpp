// config.cpp
#include "config.h"

// WiFi Credentials
const char *WIFI_SSID = "Supreme_Cat";
const char *WIFI_PASSWORD = "SuperCat063";

// Device Configuration
const char *DEVICE_ID = "INH-001";

// FSR Detection Parameters
const int FSR_THRESHOLD = 950;
const int FSR_RELEASE_THRESHOLD = 850;
const unsigned long MIN_PUFF_DURATION = 500;
const unsigned long MAX_PUFF_DURATION = 8000;
const unsigned long PUFF_COOLDOWN = 2000;

// FSR Calibration
const int BASELINE_SAMPLES = 20;

// Sensor Configuration
const unsigned long SENSOR_READ_INTERVAL = 3000;

// NTP Configuration
const long TIMEZONE_OFFSET = 21600; // Bangladesh (UTC+6)

// Device Finding
const unsigned long FIND_MODE_DURATION = 30000;