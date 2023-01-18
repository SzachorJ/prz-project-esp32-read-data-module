#include "logger.h"

String programTimeStamp()
{
    uint32_t time = millis() / 1000;
    uint8_t hours = time / 3600;
    uint8_t mins = (time - (hours * 3600)) / 60;
    uint8_t seconds = time - (hours * 3600) - (mins * 60);
    uint8_t milis = time - (hours * 3600) - (mins * 60) - (seconds * 60);
    // String timeStampTemplate = "[" + String(hours) + ":" + String(mins) + ":" + String(seconds) + "] - ";
    String timeStampTemplate = String(mins) + ":" + String(seconds) + ";";
    // String timeStampTemplate = String(seconds) + String(milis) + ";";
    return timeStampTemplate;
}

void logError(String message)
{
    Serial.print(programTimeStamp());
    Serial.print("ERROR, ");
    Serial.print(message);
    Serial.print("\n\r");
}

void logInfo(String message)
{
    Serial.print(programTimeStamp());
    Serial.print("INFO, ");
    Serial.print(message);
    Serial.print("\n\r");
}

void logData(String message)
{
    Serial.print(message);
    Serial.print("\n");
}