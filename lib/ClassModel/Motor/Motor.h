#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

// different states the motor could take
enum class MotorState {
    STOPPED,
    FORWARD,
    BACKWARD
};

class Motor {
public:
    Motor(short forwardPin, short backwardPin);

    // actions fitting for the states
    virtual void moveForward();
    virtual void moveBackward();
    virtual void stop();

    MotorState getState() const;

protected:
    short forwardPin;
    short backwardPin;
    MotorState state;
};

#endif
