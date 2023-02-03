#ifndef MAINREAD_H
#define MAINREAD_H

#include <Arduino.h>
#include <math.h>

#define MR_RPM_SIN 35
#define MR_RPM_COS 32
#define MR_V_SIN 33
#define MR_V_COS 25

#define MR_RPM_SIN_POSITIVE 26
#define MR_RPM_COS_POSITIVE 27
#define MR_V_SIN_POSITIVE 12
#define MR_V_COS_POSITIVE 14

typedef struct _main_gauge_read_
{
    uint16_t RPM_SIN;
    uint16_t RPM_COS;
    uint16_t V_SIN;
    uint16_t V_COS;
} MAIN_GAUGE_READ;

typedef struct _average_main_gauge_read_
{
    uint16_t avgRPM;
    uint16_t avgV;
} AVERAGE_MAIN_GAUGE_READ;

typedef struct _check_if_positive_
{
    uint16_t RPM_SIN_P;
    uint16_t RPM_COS_P;
    uint16_t V_SIN_P;
    uint16_t V_COS_P;
} CHECK_IF_POSITIVE;

void mainGaugePinInitialize();

MAIN_GAUGE_READ readMainGaugeValues();

CHECK_IF_POSITIVE readMainPositivity();

#endif