#include <Arduino.h>


#define RPM_INPUT A7
#define OIL_TEMP_INPUT A6
#define OIL_TEMP_OUTPUT A10

void pinInitialize(){
pinMode(RPM_INPUT, INPUT);
pinMode(OIL_TEMP_INPUT, INPUT);
pinMode(OIL_TEMP_OUTPUT, OUTPUT);
}

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}