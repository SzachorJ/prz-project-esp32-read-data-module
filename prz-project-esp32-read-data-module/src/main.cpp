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

#define V_S 36
#define V_C 37
#define RPM_S 38
#define RMP_V 39
#define OIL_T_IN 32
#define OIL_P_IN 33
#define WAT_T_IN 34
#define FUEL 35
#define ALL 4

#define OIL_T_OUT 0
#define OIL_P_OUT 2
#define WAT_T_OUT 15

#define RXD1 9
#define TXD1 10

void pinSetup()
{
  pinMode(V_S, INPUT);
  pinMode(V_C, INPUT);
  pinMode(RPM_S, INPUT);
  pinMode(RMP_V, INPUT);
  pinMode(OIL_T_IN, INPUT);
  pinMode(OIL_P_IN, INPUT);
  pinMode(WAT_T_IN, INPUT);
  pinMode(FUEL, INPUT);
  pinMode(ALL, INPUT);

  pinMode(OIL_T_OUT, OUTPUT);
  pinMode(OIL_P_OUT, OUTPUT);
  pinMode(WAT_T_OUT, OUTPUT);
}
void analogReadInput()
{
  analogRead(V_S);
  analogRead(V_C);
  analogRead(RPM_S);
  analogRead(RMP_V);
  analogRead(OIL_T_IN);
  analogRead(OIL_P_IN);
  analogRead(WAT_T_IN);
  analogRead(FUEL);
  analogRead(ALL);
}
void setup()
{
  pinSetup();

  // Serial1.begin(baud-rate, protocol, RX pin, TX pin); // dodac baud
  Serial.begin(115200);
  // Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1);
  Serial.println("Serial Txd is on pin: " + String(TX));
  Serial.println("Serial Rxd is on pin: " + String(RX));
  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:
}