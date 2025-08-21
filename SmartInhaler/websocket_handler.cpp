// websocket_handler.cpp
#include "websocket_handler.h"
#include "config.h"
#include "storage_manager.h"
#include "reminder_system.h"
#include "sensors.h"
#include "hardware.h"
#include <ArduinoJson.h>
#include <RTClib.h>

WebSocketsServer webSocket = WebSocketsServer(81);
extern RTC_DS3231 rtc;

void handleWebSocketMessage(JsonDocument &doc);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{
    switch (type)
    {
    case WStype_DISCONNECTED:
        Serial.printf("[WS %u] Disconnected\n", num);
        break;

    case WStype_CONNECTED:
    {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[WS %u] Connected from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
        broadcastSensorData();
    }
    break;

    case WStype_TEXT:
    {
        Serial.printf("[WS %u] Message: %s\n", num, payload);

        StaticJsonDocument<512> doc;
        DeserializationError error = deserializeJson(doc, payload);

        if (!error)
        {
            handleWebSocketMessage(doc);
        }
        else
        {
            Serial.print("JSON parse error: ");
            Serial.println(error.c_str());
        }
    }
    break;
    }
}

void initializeWebSocket()
{
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}

void handleWebSocket()
{
    webSocket.loop();
}

void handleWebSocketMessage(JsonDocument &doc)
{
    String command = doc["command"];

    if (command == "setReminder")
    {
        int index = doc["index"];
        if (index < 5)
        {
            setReminder(index, doc["hour"], doc["minute"], doc["label"]);
        }
    }
    else if (command == "deleteReminder")
    {
        deleteReminder(doc["index"]);
        sendReminders();
    }
    else if (command == "getReminders")
    {
        sendReminders();
    }
    else if (command == "setMaxPuffs")
    {
        setMaxPuffs(doc["maxPuffs"]);
    }
    else if (command == "resetPuffs")
    {
        resetPuffCounters();
    }
    else if (command == "findDevice")
    {
        Serial.println("Find device activated!");
        findModeActive = true;
        findModeStartTime = millis();
    }
    else if (command == "getData")
    {
        broadcastSensorData();
    }
    else if (command == "getHistory")
    {
        sendUsageHistory();
    }
    else if (command == "testHardware")
    {
        Serial.println("Hardware test requested via WebSocket");
        testHardware();
    }
}

void broadcastSensorData()
{
    StaticJsonDocument<512> doc;

    doc["type"] = "sensorData";
    doc["deviceId"] = DEVICE_ID;
    doc["temperature"] = getTemperature();
    doc["humidity"] = getHumidity();
    doc["pressure"] = getPressure();
    doc["airQuality"] = getAirQuality();
    doc["totalPuffs"] = totalPuffs;
    doc["dailyPuffs"] = dailyPuffs;
    doc["maxPuffs"] = maxPuffsPerInhaler;
    doc["ip"] = deviceIP;

    DateTime now = rtc.now();
    char timeStr[20];
    sprintf(timeStr, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
    doc["timestamp"] = timeStr;

    String output;
    serializeJson(doc, output);
    webSocket.broadcastTXT(output);
}

void sendPuffNotification()
{
    StaticJsonDocument<256> doc;
    doc["type"] = "puffDetected";
    doc["totalPuffs"] = totalPuffs;
    doc["dailyPuffs"] = dailyPuffs;
    doc["maxPuffs"] = maxPuffsPerInhaler;
    doc["temperature"] = getTemperature();
    doc["humidity"] = getHumidity();
    doc["airQuality"] = getAirQuality();
    doc["pressure"] = getPressure();

    DateTime now = rtc.now();
    char timeStr[20];
    sprintf(timeStr, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
    doc["timestamp"] = timeStr;

    String output;
    serializeJson(doc, output);
    webSocket.broadcastTXT(output);
}

void sendMaxPuffsAlert()
{
    StaticJsonDocument<256> doc;
    doc["type"] = "maxPuffsReached";
    doc["totalPuffs"] = totalPuffs;
    doc["maxPuffs"] = maxPuffsPerInhaler;

    String output;
    serializeJson(doc, output);
    webSocket.broadcastTXT(output);
}

void sendReminders()
{
    StaticJsonDocument<512> doc;
    doc["type"] = "reminders";

    JsonArray remindersArray = doc.createNestedArray("reminders");
    addRemindersToJson(remindersArray);

    String output;
    serializeJson(doc, output);
    webSocket.broadcastTXT(output);
}

void sendUsageHistory()
{
    StaticJsonDocument<512> doc;
    doc["type"] = "usageHistory";

    JsonArray historyArray = doc.createNestedArray("history");
    addUsageHistoryToJson(historyArray);

    String output;
    serializeJson(doc, output);
    webSocket.broadcastTXT(output);
}
