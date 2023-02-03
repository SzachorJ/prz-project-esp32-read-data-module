#include <Arduino.h>
#include <BluetoothSerial.h>
#include <HardwareSerial.h>
#include "converter.h"
#include "mainRead.h"
#include "secondaryRead.h"
#include "logger.h"
#include "stringAssembler.h"

#define SERIAL_BAUD 115200

BluetoothSerial BTSerial;

uint32_t programTime = 0;
uint32_t readValuesIntervalTime = 0;
uint32_t averageReadValuesIntervalTime = 0;
uint32_t averageReceivedDataIntervalTime = 0;
uint32_t sendDataIntervalTime = 0;
uint32_t averageReadCount = 0;
uint32_t averageCount = 0;
uint32_t counter = 0;
uint32_t mainCounter = 0;

uint16_t rpmMainPart = 1;
uint16_t vMainPart = 1;

MAIN_GAUGE_READ readMainValues;
MAIN_GAUGE_READ averageReadMainValues = {0, 0, 0, 0};
AVERAGE_MAIN_GAUGE_READ averageMainValues = {0, 0};

SECONDARY_GAUGE_READ readSecondaryValues;
SECONDARY_GAUGE_READ averageReadSecondaryValues = {0, 0, 0};
AVERAGE_SECONDARY_GAUGE_READ averageSecondaryValues = {0, 0, 0};

CHECK_IF_POSITIVE testPositive;

String mainOutputString;
String secondaryOutputString;
String mainOutputString2;
String secondaryOutputString2;
String widebandOutputString;
String widebandOutputString2;
String finalOutputString;
String finalOutputString2;

uint16_t calculatedRPM;
uint16_t calculatedV;
uint16_t calculatedOilT;
float calculatedOilP;
uint16_t calculatedH2OT;

void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200);
  BTSerial.begin("Projekt PRz");
  mainGaugePinInitialize();
  secondaryGaugePinInitialize();
}

void loop()
{
  programTime = millis();

  while (Serial2.available() > 0)
  {
    widebandOutputString = Serial2.readStringUntil('\n');
    // Serial.println(widebandOutputString);
    widebandOutputString.trim();
    widebandOutputString2 = widebandOutputString;

    widebandOutputString = "";
  }

  if (programTime - readValuesIntervalTime > 10)
  {
    testPositive = readMainPositivity();

    readMainValues = readMainGaugeValues();
    averageReadMainValues.RPM_SIN = averageReadMainValues.RPM_SIN + readMainValues.RPM_SIN;
    averageReadMainValues.RPM_COS = averageReadMainValues.RPM_COS + readMainValues.RPM_COS;
    averageReadMainValues.V_SIN = averageReadMainValues.V_SIN + readMainValues.V_SIN;
    averageReadMainValues.V_COS = averageReadMainValues.RPM_COS + readMainValues.V_COS;

    readSecondaryValues = readSecondaryGaugeValues();
    averageReadSecondaryValues.WT = averageReadSecondaryValues.WT + readSecondaryValues.WT;
    averageReadSecondaryValues.OP = averageReadSecondaryValues.OP + readSecondaryValues.OP;
    averageReadSecondaryValues.OT = averageReadSecondaryValues.OT + readSecondaryValues.OT;

    averageReadCount++;

    if (programTime - averageReadValuesIntervalTime > 100)
    {

      rpmMainPart = switchParts(testPositive.RPM_SIN_P, testPositive.RPM_COS_P, 200);
      vMainPart = switchParts(testPositive.V_SIN_P, testPositive.V_COS_P, 200);

      calculatedRPM = calculateRPM(calculateFinalAngle(calculateAngle(calculateRad(averageReadMainValues.RPM_SIN / averageReadCount, averageReadMainValues.RPM_COS / averageReadCount)), rpmMainPart));
      calculatedV = calculateV(calculateFinalAngle(calculateAngle(calculateRad(averageReadMainValues.V_SIN / averageReadCount, averageReadMainValues.V_COS / averageReadCount)), vMainPart));
      calculatedH2OT = calculateWaterTemp(averageReadSecondaryValues.WT / averageReadCount, MINIMUM_WT_SIGNAL, MAXIMUM_WT_SIGNAL, MINIMUM_WATER_TEMP, MAXIMUM_WATER_TEMP);
      calculatedOilP = calculateOilPress(averageReadSecondaryValues.OP / averageReadCount, MINIMUM_OP_SIGNAL, MAXIMUM_OP_SIGNAL, MINIMUM_OIL_PRESS, MAXIMUM_OIL_PRESS);
      calculatedOilT = calculatOilTemp(averageReadSecondaryValues.OT / averageReadCount, MINIMUM_OT_SIGNAL, MAXIMUM_OT_SIGNAL, MINIMUM_OIL_TEMP, MAXIMUM_OIL_TEMP);

      averageMainValues.avgRPM = averageMainValues.avgRPM + calculatedRPM;
      averageMainValues.avgV = averageMainValues.avgV + calculatedV;

      averageSecondaryValues.avgWT = averageSecondaryValues.avgWT + calculatedH2OT;
      averageSecondaryValues.avgOP = averageSecondaryValues.avgOP + calculatedOilP;
      averageSecondaryValues.avgOT = averageSecondaryValues.avgOT + calculatedOilT;

      mainOutputString = assembleMainBtOutputString((calculatedRPM), (calculatedV));
      secondaryOutputString = assembleSecondaryBtOutputString((calculatedH2OT), (calculatedOilP), (calculatedOilT));
      finalOutputString = String(counter) + mainOutputString + secondaryOutputString + widebandOutputString2;

      // Serial.println(finalOutputString);

      averageReadMainValues = {0, 0, 0, 0};
      averageReadSecondaryValues = {0, 0, 0};
      averageReadCount = 0;
      averageCount++;
      counter++;

      if (programTime - averageReceivedDataIntervalTime > 1000)
      {

        mainOutputString2 = assembleMainBtOutputString((averageMainValues.avgRPM / averageCount), (averageMainValues.avgV / averageCount));
        secondaryOutputString2 = assembleSecondaryBtOutputString((averageSecondaryValues.avgWT / averageCount), (averageSecondaryValues.avgOP / averageCount), (averageSecondaryValues.avgOT / averageCount));

        finalOutputString2 = String(mainCounter) + mainOutputString2 + secondaryOutputString2 + widebandOutputString2;

        BTSerial.print(finalOutputString2);
        Serial.println(finalOutputString2);

        averageMainValues = {0, 0};
        averageSecondaryValues = {0, 0, 0};

        averageCount = 0;
        mainCounter++;
        averageReceivedDataIntervalTime = programTime;
      }
      averageReadValuesIntervalTime = programTime;
    }

    readValuesIntervalTime = programTime;
  }
}