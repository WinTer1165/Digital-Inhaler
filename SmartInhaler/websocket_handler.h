// websocket_handler.h
#ifndef WEBSOCKET_HANDLER_H
#define WEBSOCKET_HANDLER_H

#include <WebSocketsServer.h>

void initializeWebSocket();
void handleWebSocket();
void broadcastSensorData();
void sendPuffNotification();
void sendMaxPuffsAlert();
void sendReminders();
void sendUsageHistory();

extern WebSocketsServer webSocket;

#endif