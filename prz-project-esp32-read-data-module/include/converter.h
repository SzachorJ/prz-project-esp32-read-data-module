#ifndef CONVERTER_H
#define CONVERTER_H

#include <Arduino.h>

float calculateVoltage(int signal);

float calculateRad(uint16_t sin, uint16_t cos);

uint16_t calculateAngle(float rad);

uint16_t calculateFinalAngle(uint16_t angle, uint16_t part);

uint16_t switchParts(uint16_t sinp, uint16_t cosp, uint16_t zeroValue);

uint16_t calculateRPM(uint16_t angle);

uint16_t calculateV(uint16_t angle);

uint16_t calculateWaterTemp(uint16_t signal, uint16_t min_sig, uint16_t max_sig, uint16_t min_val, uint16_t max_val);

float calculateOilPress(uint16_t signal, uint16_t min_sig, uint16_t max_sig, uint16_t min_val, uint16_t max_val);

uint16_t calculatOilTemp(uint16_t signal, uint16_t min_sig, uint16_t max_sig, uint16_t min_val, uint16_t max_val);

#endif