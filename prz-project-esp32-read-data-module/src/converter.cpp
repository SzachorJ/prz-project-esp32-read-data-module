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

uint16_t calculateAngle(float rad)
{
    uint16_t angle = ((rad * 180) / PI);
    return angle;
}

uint16_t calculateFinalAngle(uint16_t angle, uint16_t part)
{
    if (part == 1)
        return angle;
    if (part == 2)
        return (180 - angle);
    if (part == 3)
        return (180 + angle);
    if (part == 4)
        return (360 - angle);
}

uint16_t switchParts(uint16_t sinp, uint16_t cosp, uint16_t zeroValue)
{

    if (sinp >= zeroValue && cosp >= zeroValue)
    {
        return 1;
    }
    if (sinp >= zeroValue && cosp < zeroValue)
    {
        return 2;
    }

    if (sinp < zeroValue && cosp < zeroValue)
    {
        return 3;
    }

    if (sinp < zeroValue && cosp >= zeroValue)
    {
        return 4;
    }
}

uint16_t calculateRPM(uint16_t angle)
{
    uint16_t RPM;
    RPM = angle * 30;
    return RPM;
}

uint16_t calculateV(uint16_t angle)
{
    uint16_t V;
    V = angle * 0.75;
    if (V > 200)
        V = 0;
    return V;
}

uint16_t calculateWaterTemp(uint16_t signal, uint16_t min_sig, uint16_t max_sig, uint16_t min_val, uint16_t max_val)
{
    uint16_t invertedSignal = 4095 - signal;
    uint16_t trueSignal = invertedSignal - min_sig;
    uint16_t endValue = 0;
    if (invertedSignal >= min_sig && invertedSignal <= max_sig)
        endValue = 40 + trueSignal * 0.067;
    else if (invertedSignal > max_sig)
        endValue = max_val;
    else if (invertedSignal < min_sig)
        endValue = min_val;
    return endValue;
}

float calculateOilPress(uint16_t signal, uint16_t min_sig, uint16_t max_sig, uint16_t min_val, uint16_t max_val)
{
    uint16_t trueSignal = signal - min_sig;
    float endValue = 0;
    if (signal >= min_sig && signal <= max_sig)
        endValue = trueSignal * 0.006;
    else if (signal > max_sig)
        endValue = max_val;
    else if (signal < min_sig)
        endValue = min_val;
    return endValue;
}

uint16_t calculatOilTemp(uint16_t signal, uint16_t min_sig, uint16_t max_sig, uint16_t min_val, uint16_t max_val)
{
    uint16_t invertedSignal = 4095 - signal;
    uint16_t trueSignal = invertedSignal - min_sig;
    uint16_t endValue = 0;
    if (invertedSignal >= min_sig && invertedSignal <= max_sig)
        endValue = 50 + trueSignal * 0.067;
    else if (invertedSignal > max_sig)
        endValue = max_val;
    else if (invertedSignal < min_sig)
        endValue = min_val;
    return endValue;
}