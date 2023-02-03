#ifndef SECONDARYREAD_H
#define SECONDARYREAD_H

#include <Arduino.h>
#include <math.h>

#define SR_WATERTEMP 36
#define SR_OILPRESS 34
#define SR_OILTEMP 39

#define MINIMUM_WATER_TEMP 40
#define MAXIMUM_WATER_TEMP 120

#define MINIMUM_OIL_PRESS 0
#define MAXIMUM_OIL_PRESS 7

#define MINIMUM_OIL_TEMP 50
#define MAXIMUM_OIL_TEMP 150

#define MINIMUM_WT_SIGNAL 1145
#define MAXIMUM_WT_SIGNAL 2345

#define MINIMUM_OP_SIGNAL 750
#define MAXIMUM_OP_SIGNAL 1900

#define MINIMUM_OT_SIGNAL 1945
#define MAXIMUM_OT_SIGNAL 3445

typedef struct _secondary_gauge_read_
{
    uint16_t WT;
    float OP;
    uint16_t OT;
} SECONDARY_GAUGE_READ;

typedef struct _average_secondary_gauge_read_
{
    uint16_t avgWT;
    float avgOP;
    uint16_t avgOT;
} AVERAGE_SECONDARY_GAUGE_READ;

void secondaryGaugePinInitialize();

SECONDARY_GAUGE_READ readSecondaryGaugeValues();

#endif