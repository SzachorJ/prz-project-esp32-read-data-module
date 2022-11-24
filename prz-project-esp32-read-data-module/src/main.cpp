#include <Arduino.h>

#define V_S 36
#define V_C 37
#define RPM_S 38
#define RPM_C ...
#define OIL_TEMP_OUT 1

void pinSetUp()
{
  pinMode(V_S, INPUT);
  pinMode(OIL_TEMP_OUT, OUTPUT);
}

void setup()
{

  pinSetUp();
  // put your setup code here, to run once:
}

void loop()
{

  Serial.print("ok");
  // put your main code here, to run repeatedly:
}