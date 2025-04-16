#include "Motor.h"

Motor::Motor(short forwardPin, short backwardPin)
    : forwardPin(forwardPin)
    , backwardPin(backwardPin)
    , state(MotorState::STOPPED)
{
    // init state
    pinMode(forwardPin, OUTPUT);
    if (backwardPin != -1) {
        // -1 means not used
        pinMode(backwardPin, OUTPUT);
    }
    stop();
}

void Motor::moveForward()
{
    digitalWrite(forwardPin, HIGH);
    if (backwardPin != -1) {

        digitalWrite(backwardPin, LOW);
    }
    state = MotorState::FORWARD;
}

void Motor::moveBackward()
{
    digitalWrite(forwardPin, LOW);
    if (backwardPin != -1) {

        digitalWrite(backwardPin, HIGH);
    }
    state = MotorState::BACKWARD;
}

void Motor::stop()
{
    digitalWrite(forwardPin, LOW);
    if (backwardPin != -1) {
        digitalWrite(backwardPin, LOW);
    }
    state = MotorState::STOPPED;
}

MotorState Motor::getState() const
{
    return state;
}
