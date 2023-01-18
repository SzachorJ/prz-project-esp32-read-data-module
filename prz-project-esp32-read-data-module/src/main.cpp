#include <Arduino.h>
#include <BluetoothSerial.h>
#include "converter.h"
#include "secondaryRead.h"
#include "mainRead.h"
#include "logger.h"

#define SERIAL_BAUD 9600

BluetoothSerial BTSerial;

uint32_t programTime = 0;
uint32_t readMainValuesIntervalTime = 0;
uint32_t sendTestDataIntervalTime = 0;
uint32_t readSecondaryValuesIntervalTime = 0;
uint32_t displayValuesIntervalTime = 0;
uint32_t count = 0;
uint32_t counter = 0;

MAIN_GAUGE_READ readMainValues;
MAIN_GAUGE_READ averageMainValues = {0, 0, 0, 0};
SECONDARY_GAUGE_READ readSecondaryValues;
SECONDARY_GAUGE_READ averageSecondaryValues = {0, 0, 0};

String secondaryTestOutputString;
String mainTestOutputString;
String secondaryBtOutputString;
String mainBtOutputString;
String logString;

uint16_t part = 1;

void setup()
{
  Serial.begin(SERIAL_BAUD);
  BTSerial.begin("test");
  mainGaugePinInitialize();
  secondaryGaugePinInitialize();
}

void loop()
{
  programTime = millis();
  int output = 0;
  if (programTime - readMainValuesIntervalTime > 10)
  {
    readMainValues = readMainGaugeValues();
    averageMainValues.RPM_SIN = averageMainValues.RPM_SIN + readMainValues.RPM_SIN;
    averageMainValues.RPM_COS = averageMainValues.RPM_COS + readMainValues.RPM_COS;
    averageMainValues.V_SIN = averageMainValues.V_SIN + readMainValues.V_SIN;
    averageMainValues.V_COS = averageMainValues.V_COS + readMainValues.V_COS;

    readSecondaryValues = readSecondaryGaugeValues();
    averageSecondaryValues.WT = averageSecondaryValues.WT + readSecondaryValues.WT;
    averageSecondaryValues.OP = averageSecondaryValues.OP + readSecondaryValues.OP;
    averageSecondaryValues.OT = averageSecondaryValues.OT + readSecondaryValues.OT;

    count++;
    if (programTime - sendTestDataIntervalTime > 100)
    {
      secondaryTestOutputString = testSecondary(averageSecondaryValues.WT / count, averageSecondaryValues.OP / count, averageSecondaryValues.OT / count);
      mainTestOutputString = testMain(averageMainValues.RPM_SIN / count, averageMainValues.RPM_COS / count, averageMainValues.V_SIN / count, averageMainValues.V_COS / count);
      logString = String(counter) + "-" + mainTestOutputString + "-" + secondaryTestOutputString;
      logData(logString);
      averageMainValues = {0, 0, 0, 0};
      averageSecondaryValues = {0, 0, 0};
      count = 0;
      counter++;

      if (programTime - displayValuesIntervalTime > 1000)
      {
        mainBtOutputString = assembleMainBtOutputString();
        secondaryBtOutputString = assembleSecondaryBtOutputString();
        BTSerial.print(mainBtOutputString);
        BTSerial.print("\n");
        BTSerial.print(secondaryBtOutputString);
        BTSerial.print("\n");

        displayValuesIntervalTime = programTime;
      }
      sendTestDataIntervalTime = programTime;
    }

    readMainValuesIntervalTime = programTime;
  }
}