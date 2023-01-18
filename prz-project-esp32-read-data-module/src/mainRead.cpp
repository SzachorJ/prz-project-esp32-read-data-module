#include "mainRead.h"
#include "converter.h"
#include "logger.h"

MAIN_GAUGE_READ mainGaugeValues = {0, 0, 0, 0};

void mainGaugePinInitialize()
{
    pinMode(MR_RPM_SIN, INPUT);
    pinMode(MR_RPM_COS, INPUT);
    pinMode(MR_V_SIN, INPUT);
    pinMode(MR_V_COS, INPUT);
    logInfo("main pin initialization complete");
}

MAIN_GAUGE_READ readMainGaugeValues()
{
    mainGaugeValues.RPM_SIN = analogRead(MR_RPM_SIN);
    mainGaugeValues.RPM_COS = analogRead(MR_RPM_COS);
    mainGaugeValues.V_SIN = analogRead(MR_V_SIN);
    mainGaugeValues.V_COS = analogRead(MR_V_COS);

    return mainGaugeValues;
}

String assembleMainBtOutputString()
{
    String outputString = "";
    outputString += "RPM ALPHA: ";
    outputString += String(calculateAngle(calculateRad(mainGaugeValues.RPM_SIN, mainGaugeValues.RPM_COS)));
    outputString += " V_ALPHA: ";
    outputString += String(calculateAngle(calculateRad(mainGaugeValues.V_SIN, mainGaugeValues.V_COS)));

    return outputString;
}

String testMain(int a, int b, int c, int d)
{
    String testString = "";
    testString += "RPM_SIN-";
    testString += String(a);
    testString += ";RPM_COS-";
    testString += String(b);
    testString += ";RAD-";
    testString += String(calculateRad(a, b));
    testString += ";ALPHA-";
    testString += String(calculateAngle(calculateRad(a, b)));
    testString += ";V_SIN-";
    testString += String(c);
    testString += ";V_COS-";
    testString += String(d);
    testString += ";RAD-";
    testString += String(calculateRad(c, d));
    testString += ";V_ALPHA-";
    testString += String(calculateAngle(calculateRad(c, d)));

    return testString;
}
