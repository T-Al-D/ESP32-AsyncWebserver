#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class Sensor {
public:
    Sensor(short inputPin, int threshold = 1);

    bool isTriggered() const;

private:
    short pin;
    int triggerThreshold;
};

#endif