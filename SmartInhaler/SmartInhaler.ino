/**
 * Smart Inhaler System
 * Version: 1.0
 */

#include "config.h"
#include "hardware.h"
#include "sensors.h"
#include "network.h"
#include "websocket_handler.h"
#include "display_manager.h"
#include "puff_detector.h"
#include "reminder_system.h"
#include "storage_manager.h"
#include "time_manager.h"

void setup()
{
    Serial.begin(115200);
    Serial.println("\n=== Smart Inhaler System V1.0 ===");

    // Initialize storage first
    initializeStorage();
    loadAllSettings();

    // Initialize hardware components
    initializeHardware();

    // Initialize display
    initializeDisplay();
    showBootScreen();

    // Initialize sensors
    initializeSensors();

    // Initialize time management
    initializeTimeManager();

    // Connect to network
    connectToWiFi();

    // Setup web services
    setupWebServer();
    initializeWebSocket();

    // Initialize subsystems
    initializePuffDetector();
    initializeReminderSystem();
    initializeUsageHistory();

    // Test hardware
    testHardware();

    Serial.println("=== System Ready ===");
    Serial.print("Access web interface at: http://");
    Serial.println(getDeviceIP());
}

void loop()
{
    // Handle network services
    handleWebServer();
    handleWebSocket();

    // Update time periodically
    updateTimeFromNTP();

    // Detect puffs
    detectPuff();

    // Check reminders
    checkReminders();

    // Handle find mode
    handleFindMode();

    // Read sensors periodically
    static unsigned long lastSensorRead = 0;
    if (millis() - lastSensorRead > SENSOR_READ_INTERVAL)
    {
        readSensors();
        lastSensorRead = millis();
    }

    // Broadcast data periodically
    static unsigned long lastBroadcast = 0;
    if (millis() - lastBroadcast > 5000)
    {
        broadcastSensorData();
        lastBroadcast = millis();
    }

    // Update display
    updateDisplay();

    // Check daily reset
    checkDailyReset();

    delay(10);
}