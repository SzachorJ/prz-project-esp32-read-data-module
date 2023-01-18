#ifndef CONVERTER_H
#define CONVERTER_H

#include <Arduino.h>

float calculateVoltage(int signal);

float calculateRad(uint16_t sin, uint16_t cos);

float calculateAngle(float rad);

uint16_t calculatePart(float angle, uint16_t part);

float finalAngle(float angle, uint16_t part);

#endif