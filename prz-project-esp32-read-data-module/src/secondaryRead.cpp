#include "secondaryRead.h"
#include "converter.h"

SECONDARY_GAUGE_READ secondaryGaugeValues = {0, 0, 0};

void secondaryGaugePinInitialize()
{
    pinMode(SR_WATERTEMP, INPUT);
    pinMode(SR_OILPRESS, INPUT);
    pinMode(SR_OILTEMP, INPUT);
}

SECONDARY_GAUGE_READ readSecondaryGaugeValues()
{
    secondaryGaugeValues.WT = analogRead(SR_WATERTEMP);
    secondaryGaugeValues.OP = analogRead(SR_OILPRESS);
    secondaryGaugeValues.OT = analogRead(SR_OILTEMP);

    return secondaryGaugeValues;
}
