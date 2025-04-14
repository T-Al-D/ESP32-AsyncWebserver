#ifndef SLIDE_MOTOR_H
#define SLIDE_MOTOR_H

#include "Motor/Motor.h"

class SlideMotor : public Motor {
public:
    SlideMotor(short forwardPin, short backwardPin);
};

#endif
