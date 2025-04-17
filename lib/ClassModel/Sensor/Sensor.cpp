#include "Sensor.h"

Sensor::Sensor(short inputPin, int threshold)
    : pin(inputPin)
    , triggerThreshold(threshold)
{
    // pinMode(pin, INPUT_PULLDOWN);
    pinMode(pin, ANALOG);
}

bool Sensor::isTriggered() const
{
    int value = analogRead(pin);
    bool returnValue = false;

    if (value < triggerThreshold) {
        returnValue = true;
        char stringBuffer[70];
        sprintf(stringBuffer, "SensorPin %d: %d", pin, value);
        Serial.println(stringBuffer);
    }

    return returnValue;
}