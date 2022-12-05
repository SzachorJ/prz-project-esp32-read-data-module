#include <Arduino.h>

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
float *analogReadInput()
{
  float x1 = analogRead(V_S);
  float x2 = analogRead(V_C);
  float x3 = analogRead(RPM_S);
  float x4 = analogRead(RMP_V);
  float x5 = analogRead(OIL_T_IN);
  float x6 = analogRead(OIL_P_IN);
  float x7 = analogRead(WAT_T_IN);
  float x8 = analogRead(FUEL);
  float x9 = analogRead(ALL);
  float x[] = {x1, x2, x3, x4, x5, x6, x7, x8, x9};
  return x; // czy te zmienne sa niszczone po returnie?
}
float *analogReadAverage()
{
  float x[90] = {};
  for (int i = 0, j = 0; i < 90; j = 0)
  {
    float *l = analogReadInput();
    while (j < 9)
    {
      x[i] = l[j];
      i++;
      j++;
    }
    // czasomierz 100ms
  }
  float y[9] = {};
  for (int i = 0, j = 0; j < 9; i = 0, j++)
  {
    while (i < 90)
    {
      y[j] += x[j + i];
      i += 9;
    }
    y[j] = y[j] / 10;
  }
  return y;
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
  analogReadInput();
  // put your main code here, to run repeatedly:
}