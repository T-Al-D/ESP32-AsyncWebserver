#ifndef CONVEYOR_BELT_H
#define CONVEYOR_BELT_H

#include "Motor/Motor.h"

class ConveyorBelt : public Motor {
public:
    ConveyorBelt(short forwardPin, short backwardPin);
};

#endif