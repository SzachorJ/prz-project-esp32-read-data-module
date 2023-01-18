#ifndef SECONDARYREAD_H
#define SECONDARYREAD_H

#include <Arduino.h>
#include <math.h>

#define SR_WATERTEMP 34
#define SR_OILPRESS 35
#define SR_OILTEMP 32

#define MINIMUM_WATER_TEMP 40
#define MAXIMUM_WATER_TEMP 120

#define MINIMUM_OIL_PRESS 0
#define MAXIMUM_OIL_PRESS 7

#define MINIMUM_OIL_TEMP 50
#define MAXIMUM_OIL_TEMP 150

#define MINIMUM_WT_SIGNAL 300
#define MAXIMUM_WT_SIGNAL 3900

#define MINIMUM_OP_SIGNAL 300
#define MAXIMUM_OP_SIGNAL 3900

#define MINIMUM_OT_SIGNAL 300
#define MAXIMUM_OT_SIGNAL 3900

typedef struct _secondary_gauge_read_
{
    uint16_t WT;
    uint16_t OP;
    uint16_t OT;
} SECONDARY_GAUGE_READ;

void secondaryGaugePinInitialize();

SECONDARY_GAUGE_READ readSecondaryGaugeValues();

boolean isWaterTempInRange(uint16_t signal);

float calculateWaterTemp(uint16_t signal);

boolean isOilPressInRange(uint16_t signal);

float calculateOilPress(uint16_t signal);

boolean isOilTempInRange(uint16_t signal);

float calculatOilTemp(uint16_t signal);

String assembleSecondaryBtOutputString();

String testSecondary(uint16_t a, uint16_t b, uint16_t c);

#endif