#include "mainRead.h"
#include "converter.h"

MAIN_GAUGE_READ mainGaugeValues = {0, 0, 0, 0};

CHECK_IF_POSITIVE positiveValues = {0, 0, 0, 0};

void mainGaugePinInitialize()
{
    pinMode(MR_RPM_SIN, INPUT);
    pinMode(MR_RPM_COS, INPUT);
    pinMode(MR_V_SIN, INPUT);
    pinMode(MR_V_COS, INPUT);
    pinMode(MR_RPM_SIN_POSITIVE, INPUT);
    pinMode(MR_RPM_COS_POSITIVE, INPUT);
    pinMode(MR_V_SIN_POSITIVE, INPUT);
    pinMode(MR_V_COS_POSITIVE, INPUT);
}

MAIN_GAUGE_READ readMainGaugeValues()
{
    mainGaugeValues.RPM_SIN = analogRead(MR_RPM_SIN);
    mainGaugeValues.RPM_COS = analogRead(MR_RPM_COS);
    mainGaugeValues.V_SIN = analogRead(MR_V_SIN);
    mainGaugeValues.V_COS = analogRead(MR_V_COS);
    return mainGaugeValues;
}

CHECK_IF_POSITIVE readMainPositivity()
{
    positiveValues.RPM_SIN_P = analogRead(MR_RPM_SIN_POSITIVE);
    positiveValues.RPM_COS_P = analogRead(MR_RPM_COS_POSITIVE);
    positiveValues.V_SIN_P = analogRead(MR_V_SIN_POSITIVE);
    positiveValues.V_COS_P = analogRead(MR_V_COS_POSITIVE);
    return positiveValues;
}
