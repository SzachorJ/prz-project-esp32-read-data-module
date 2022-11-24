#include <Arduino.h>
#include <analog_write.h>

#define pin_a 8

const int pwm = 123;

void setup()
{

  pinMode(pin_a, OUTPUT);
  // put your setup code here, to run once:
}

void loop()
{

  analogWrite(pin_a, pwm);
  // put your main code here, to run repeatedly:
}