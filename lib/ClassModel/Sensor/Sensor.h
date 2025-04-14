#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class Sensor {
public:
    Sensor(short inputPin);

    bool isTriggered() const;

private:
    short pin;
};

#endif