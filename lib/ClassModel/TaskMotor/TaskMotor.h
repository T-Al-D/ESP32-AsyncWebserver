#ifndef TASK_MOTOR_H
#define TASK_MOTOR_H

#include "Motor/Motor.h"

class TaskMotor : public Motor {
public:
    TaskMotor(short forwardPin, short backwardPin);
};

#endif