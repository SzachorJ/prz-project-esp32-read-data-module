#ifndef MAINREAD_H
#define MAINREAD_H

#include <Arduino.h>
#include <math.h>

#define MR_RPM_SIN 33
#define MR_RPM_COS 25
#define MR_V_SIN 26
#define MR_V_COS 27

#define MINIMUM_RPM 500
#define MAXIMUM_RPM 7000

#define MINIMUM_V 0
#define MAXIMUM_V 220

#define MINIMUM_RPM_SIN_SIGNAL 220
#define MAXIMUM_RPM_COS_SIGNAL 2160

#define MINIMUM_V_SIN_SIGNAL 150
#define MAXIMUM_V_COS_SIGNAL 2130

typedef struct _main_gauge_read_
{
    uint16_t RPM_SIN;
    uint16_t RPM_COS;
    uint16_t V_SIN;
    uint16_t V_COS;
} MAIN_GAUGE_READ;

void mainGaugePinInitialize();

MAIN_GAUGE_READ readMainGaugeValues();

String assembleMainBtOutputString();

String testMain(int a, int b, int c, int d);
#endif