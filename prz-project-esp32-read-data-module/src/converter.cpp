#include "converter.h"

float calculateVoltage(int signal)
{
    float voltage = 0;
    voltage = (float)signal / 4095 * 3.3 / 10000 * 4700;
    return voltage;
}

float calculateRad(uint16_t sin, uint16_t cos)
{
    if (cos == 0)
        cos = 1;
    float rad = atan(calculateVoltage(sin) / calculateVoltage(cos));
    return rad;
}

float calculateAngle(float rad)
{
    float angle = ((rad * 180) / PI);
    return angle;
}

uint16_t calculatePart(float angle, uint16_t part)
{
    int newPart = 1;

    if (angle + 1 > 90 && part == 1)
    {
        newPart = 2;
        return newPart;
    }

    if (angle + 1 > 90 && part == 2)
    {
        newPart = 1;
        return newPart;
    }
    if (angle - 1 < 0 && part == 2)
    {
        newPart = 3;
        return newPart;
    }

    if (angle - 1 < 0 && part == 3)
    {
        newPart = 2;
        return newPart;
    }
    if (angle + 1 > 90 && part == 3)
    {
        newPart = 4;
        return newPart;
    }

    if (angle + 1 > 90 && part == 4)
    {
        newPart = 3;
        return newPart;
    }
}

float finalAngle(float angle, uint16_t part)
{
    float finalAngle = 0;
    if (part == 1)
    {
        finalAngle = angle;
        return finalAngle;
    }
    if (part == 2)
    {
        finalAngle = 180 - angle;
        return finalAngle;
    }
    if (part == 3)
    {
        finalAngle = 180 + angle;
        return finalAngle;
    }
    if (part == 4)
    {
        finalAngle = 360 - angle;
        return finalAngle;
    }
}