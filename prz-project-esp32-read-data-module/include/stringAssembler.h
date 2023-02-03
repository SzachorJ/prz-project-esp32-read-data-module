#ifndef STRINGASSEMBLER_H
#define STRINGASSEMBLER_H

#include <Arduino.h>

String assembleSecondaryBtOutputString(uint16_t wt, float op, uint16_t ot);

String assembleMainBtOutputString(uint16_t rpm, uint16_t v);

#endif