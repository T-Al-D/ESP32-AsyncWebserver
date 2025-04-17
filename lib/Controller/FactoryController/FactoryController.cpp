#include "FactoryController.h"

// import global variables
extern String output;

/////////////////////////// Pin Definitions //////////////////////////
// define the pins
// 5 inputs for the factory simulation
const short INPUT_1 = 7;
const short INPUT_2 = 6;
const short INPUT_3 = 5;
const short INPUT_4 = 4;
const short INPUT_5 = 3;

// sequence of operations -> in this order !
const short CONVEYOR_BELT_1_OUT = 48;
const short SLIDE_MOTOR_1_FORWARD_OUT = 47;
const short SLIDE_MOTOR_1_BACKWARD_OUT = 45;
const short CONVEYOR_BELT_2_OUT = 33;
const short TASK_MOTOR_1_OUT = 34;

const short CONVEYOR_BELT_3_OUT = 38;
const short TASK_MOTOR_2_OUT = 19;
const short SLIDE_MOTOR_2_FORWARD_OUT = 41;
const short SLIDE_MOTOR_2_BACKWARD_OUT = 46;
const short CONVEYOR_BELT_4_OUT = 42;

// time for specifc operations
const short SWITCH_BELT_TO_SLIDE_TIME = 1900;
const short SLIDE_MOVE_TIME = 2075;
const short TASK_TIME = 3000;

/////////////////////////// FACTORY SIMULATION //////////////////////////

// -1 is used to mark the pin as UNUSED
FactoryController::FactoryController()
    : belt1(CONVEYOR_BELT_1_OUT, -1)
    , belt2(CONVEYOR_BELT_2_OUT, -1)
    , belt3(CONVEYOR_BELT_3_OUT, -1)
    , belt4(CONVEYOR_BELT_4_OUT, -1)
    , slide1(SLIDE_MOTOR_1_FORWARD_OUT, SLIDE_MOTOR_1_BACKWARD_OUT)
    , slide2(SLIDE_MOTOR_2_FORWARD_OUT, SLIDE_MOTOR_2_BACKWARD_OUT)
    , task1(TASK_MOTOR_1_OUT, -1)
    , task2(TASK_MOTOR_2_OUT, -1)
    , input1(INPUT_1)
    , input2(INPUT_2)
    , input3(INPUT_3)
    , input4(INPUT_4)
    , input5(INPUT_5)
    , objectTimestamp(0)
    , slideMotorTimestamp(0)
{
    task1AlreadyActive = false;
    task2AlreadyActive = false;
}

void FactoryController::setupFactoryController()
{
    // Serial.begin(115200);
    // pin configuration in the constructor
}

void FactoryController::loopFactoryController()
{
    // get current milliseconds since start
    unsigned long now = millis();

    processLogic(now);
    updateActuators();
}

void FactoryController::processLogic(unsigned long now)
{
    // timemeasurement: differences between 2 timestamps
    unsigned long objTimeDiff = objectTimestamp > 0 ? now - objectTimestamp : 0;
    unsigned long slideTimeDiff = slideMotorTimestamp > 0 ? now - slideMotorTimestamp : 0;

    if (input1.isTriggered()) {
        belt1.moveForward();
        output = "BELT1 active";
        Serial.println("INPUT_1: belt1 is active");
    }

    else if (input2.isTriggered()) {
        objectTimestamp = now;
        output = "SET\nTIMESTAMP";
        Serial.println("INPUT_2: Object identified, setting timestamp");
    }

    else if (objTimeDiff > SWITCH_BELT_TO_SLIDE_TIME && belt1.getState() == MotorState::FORWARD) {
        belt1.stop();
        slide1.moveForward();
        belt2.moveForward();
        slideMotorTimestamp = now;
        output = "SLIDE1\nBELT2\nFORWARD";
        Serial.println("slide1 forward, belt2 active");
    }

    else if (input3.isTriggered() && task1AlreadyActive == false) {
        belt2.stop();
        task1.moveForward();
        objectTimestamp = now;
        task1AlreadyActive = true;
        output = "TASK1\nworking\n...";
        Serial.println("INPUT_3: task1 working ...");
    }

    else if (objTimeDiff > TASK_TIME && task1.getState() == MotorState::FORWARD) {
        task1.stop();
        belt2.moveForward();
        belt3.moveForward();
        output = "BELT1, BELT2\nACTIVE";
        Serial.println("task1 finished, belt2 und 3 active");
    }

    else if (input4.isTriggered() && task2AlreadyActive == false) {
        task2.moveForward();
        belt2.stop();
        belt3.stop();
        task2AlreadyActive = true;
        objectTimestamp = now;
        output = "TASK2 \nworking..\n BELT1, 2 work";
        Serial.println("INPUT_4: task2 working ...");
    }

    else if (objTimeDiff > TASK_TIME && task2.getState() == MotorState::FORWARD) {
        task2.stop();
        belt3.moveForward();
        objectTimestamp = now;
        output = "TASK2 \nfinished..\n BELT3 active";
        Serial.println("task2 finish, belt3 active");
    }

    else if (objTimeDiff > TASK_TIME && belt3.getState() == MotorState::FORWARD
        && belt2.getState() != MotorState::FORWARD) {
        slide2.moveForward();
        belt3.stop();
        belt4.moveForward();
        slideMotorTimestamp = now;
        output = "SLIDE2, BELT4\nworking...";
        Serial.println("slide2 FORWARD, belt4 START");
    }

    else if (input5.isTriggered()) {
        Serial.println("INPUT_5: END reached, STOP everything and reset!");
        output = "RESET ALL!";
        reset();
    }

    if (slideTimeDiff > SLIDE_MOVE_TIME) {
        if (slide1.getState() == MotorState::FORWARD) {
            slide1.moveBackward();
            slideMotorTimestamp = now;
            output = "SLIDE1\nBACKWARD!";
            Serial.println("slide1 BACKWARD");
        } else if (slide1.getState() == MotorState::BACKWARD) {
            slide1.stop();
            slideMotorTimestamp = 0;
            output = "SLIDE1\nSTOP!";
            Serial.println("slide1 STOP");
        }

        if (slide2.getState() == MotorState::FORWARD) {
            slide2.moveBackward();
            slideMotorTimestamp = now;
            output = "SLIDE2\nBACKWARD!";
            Serial.println("slide2 BACKWARD");
        } else if (slide2.getState() == MotorState::BACKWARD) {
            slide2.stop();
            slideMotorTimestamp = 0;
            output = "SLIDE1\nSTOP!";
            Serial.println("slide2 STOP");
        }
    }
}

void FactoryController::updateActuators()
{
    // currently not needed, pins are controlled with start()/stop() directly
    // reserved for more logic (PWM, Safety, etc.)
}

void FactoryController::reset()
{
    belt1.stop();
    belt2.stop();
    belt3.stop();
    belt4.stop();

    slide1.stop();
    //slide2.stop();

    task1.stop();
    task2.stop();

    objectTimestamp = 0;
    //slideMotorTimestamp = 0;

    task1AlreadyActive = false;
    task2AlreadyActive = false;

    Serial.println("Everything reset!");
}
