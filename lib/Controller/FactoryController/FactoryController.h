#ifndef FACTORY_CONTROLLER_H
#define FACTORY_CONTROLLER_H

#include "../ClassModel/ConveyorBelt/ConveyorBelt.h"
#include "../ClassModel/Sensor/Sensor.h"
#include "../ClassModel/SlideMotor/SlideMotor.h"
#include "../ClassModel/TaskMotor/TaskMotor.h"
#include <Arduino.h>

class FactoryController {
public:
    FactoryController();
    void setupFactoryController();
    void loopFactoryController();
    void reset();

    // all the different motors
    ConveyorBelt belt1, belt2, belt3, belt4;
    SlideMotor slide1, slide2;
    TaskMotor task1, task2;

private:
    // all sensors
    Sensor input1, input2, input3, input4, input5;

    // timestamps for "timemeasurement"
    unsigned long objectTimestamp;
    unsigned long slideMotorTimestamp;

    // logic
    void processLogic(unsigned long now);
    void updateActuators();
};

#endif
