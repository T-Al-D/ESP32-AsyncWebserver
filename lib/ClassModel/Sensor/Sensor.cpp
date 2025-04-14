#include "Sensor.h"

Sensor::Sensor(short inputPin)
    : pin(inputPin)
{
    pinMode(pin, INPUT_PULLDOWN);
}

bool Sensor::isTriggered() const
{
    return digitalRead(pin) == HIGH;
}