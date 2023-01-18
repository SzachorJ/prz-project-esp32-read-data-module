#include "secondaryRead.h"
#include "logger.h"
#include "converter.h"
#include "conversion.h"

SECONDARY_GAUGE_READ secondaryGaugeValues = {0, 0, 0};

void secondaryGaugePinInitialize()
{
    pinMode(SR_WATERTEMP, INPUT);
    pinMode(SR_OILPRESS, INPUT);
    pinMode(SR_OILTEMP, INPUT);
    logInfo("secondary pin initialization complete");
}

SECONDARY_GAUGE_READ readSecondaryGaugeValues()
{
    secondaryGaugeValues.WT = analogRead(SR_WATERTEMP);
    secondaryGaugeValues.OP = analogRead(SR_OILPRESS);
    secondaryGaugeValues.OT = analogRead(SR_OILTEMP);

    return secondaryGaugeValues;
}

boolean isWaterTempInRange(uint16_t signal)
{
    return signal >= MINIMUM_WT_SIGNAL && signal <= MAXIMUM_WT_SIGNAL;
}

float calculateWaterTemp(uint16_t signal)
{
    float result;

    if (isWaterTempInRange(signal))
    {
        result = pgm_read_float_near(WATER_TEMP_CONVERSION_VALUE + (signal - MINIMUM_WT_SIGNAL));
    }
    else if (signal > MAXIMUM_WT_SIGNAL)
    {
        result = MAXIMUM_WATER_TEMP;
    }
    else
    {
        result = MINIMUM_WATER_TEMP;
    }

    return result;
}

boolean isOilPressInRange(uint16_t signal)
{
    return signal >= MINIMUM_OP_SIGNAL && signal <= MAXIMUM_OP_SIGNAL;
}

float calculateOilPress(uint16_t signal)
{
    float result;

    if (isOilPressInRange(signal))
    {
        result = pgm_read_float_near(OIL_PRESS_CONVERSION_VALUE + (signal - MINIMUM_OP_SIGNAL));
    }
    else if (signal > MAXIMUM_OP_SIGNAL)
    {
        result = MAXIMUM_OIL_PRESS;
    }
    else
    {
        result = MINIMUM_OIL_PRESS;
    }

    return result;
}

boolean isOilTempInRange(uint16_t signal)
{
    return signal >= MINIMUM_OT_SIGNAL && signal <= MAXIMUM_OT_SIGNAL;
}

float calculatOilTemp(uint16_t signal)
{
    float result;

    if (isOilTempInRange(signal))
    {
        result = pgm_read_float_near(OIL_TEMP_CONVERSION_VALUE + (signal - MINIMUM_OT_SIGNAL));
    }
    else if (signal > MAXIMUM_OT_SIGNAL)
    {
        result = MAXIMUM_OIL_TEMP;
    }
    else
    {
        result = MINIMUM_OIL_TEMP;
    }

    return result;
}

String assembleSecondaryBtOutputString()
{
    String outputString = "";
    outputString += "WT: ";
    outputString += String(secondaryGaugeValues.WT);

    outputString += " OP: ";
    outputString += String(secondaryGaugeValues.OP);

    outputString += " OT: ";
    outputString += String(secondaryGaugeValues.OT);

    return outputString;
}

String testSecondary(uint16_t a, uint16_t b, uint16_t c)
{
    String testString = "";
    testString += ";WT-";
    testString += String(a);
    testString += ";OP-";
    testString += String(b);
    testString += ";OT-";
    testString += String(c);
    testString += ";";

    return testString;
}
