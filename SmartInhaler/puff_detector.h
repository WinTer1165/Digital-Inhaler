// puff_detector.h
#ifndef PUFF_DETECTOR_H
#define PUFF_DETECTOR_H

#include <Arduino.h>

void initializePuffDetector();
void detectPuff();
void calibrateFSR();

extern bool isPuffing;
extern unsigned long lastPuffTime;

#endif