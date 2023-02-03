#include "stringAssembler.h"

String assembleSecondaryBtOutputString(uint16_t wt, float op, uint16_t ot)
{
    String outputString = "";
    outputString += ":";
    outputString += String(wt);

    outputString += ":";
    outputString += String(op);

    outputString += ":";
    outputString += String(ot);

    return outputString;
}

String assembleMainBtOutputString(uint16_t rpm, uint16_t v)
{
    String outputString = "";
    outputString += ":";
    outputString += String(rpm);
    outputString += ":";
    outputString += String(v);

    return outputString;
}