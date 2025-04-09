#include "StatusControl.h"

/* [env:esp32-s3-devkitm-1]
LED1 = 46;LED2 = 45;
PHOTO_RESISTOR_1 = 1; P_R_2 = 2;

[env:az-delivery-devkit-v4]
LED1 = 32;LED2 = 33;
PHOTO_RESISTOR_1 = 0; P_R_2 = 2;
*/

// define the pins
const short PHOTO_RESISTOR_1 = 1;
const short PHOTO_RESISTOR_2 = 2;

const short LED1 = 46;
const short LED2 = 45;

// define statuses
bool button1Status = false;
bool button2Status = false;

/////////////////////////// FACTORY SIMULATION //////////////////////////
// 5 inputs for the factory simulation
const short INPUT_1 = 7;
const short INPUT_2 = 6;
const short INPUT_3 = 5;
const short INPUT_4 = 4;
const short INPUT_5 = 3;

short conveyorBelt1Status = 0;
short conveyorBelt2Status = 0;
short conveyorBelt3Status = 0;
short conveyorBelt4Status = 0;

short slideMotor1Status = 0;
short slideMotor2Status = 0;

short taskMotor1Status = 0;
short taskMotor2Status = 0;

// sequence of operations
const short CONVEYOR_BELT_1_OUT = 48;
const short SLIDE_MOTOR_1_OUT = 47;
const short CONVEYOR_BELT_2_OUT = 33;
const short TASK_MOTOR_1_OUT = 34;

const short CONVEYOR_BELT_3_OUT = 38;
const short TASK_MOTOR_2_OUT = 19;
const short SLIDE_MOTOR_2_OUT = 41;
const short CONVEYOR_BELT_4_OUT = 42;

// time for specifc operations
const short SWITCH_BELT_TO_SLIDE_TIME = 3000;
const short SLIDE_MOVE_TIME = 2000;
const short TASK_TIME = 3000;

// for measuring time
unsigned long objectTimestamp = 0;
unsigned long objTimeDiff = 0;
unsigned long slideMotorTimeStamp = 0;
unsigned long slideMotorTimeDiff = 0;

/////////////////////////// FACTORY SIMULATION //////////////////////////

// "import" global variables
extern String output;
extern unsigned long currentMilliSeconds;

void setPins()
{
    // set inputs
    pinMode(PHOTO_RESISTOR_1, INPUT);
    pinMode(PHOTO_RESISTOR_2, INPUT);

    // default:0 , if connect to +: 1
    pinMode(INPUT_1, INPUT_PULLDOWN);
    pinMode(INPUT_2, INPUT_PULLDOWN);
    pinMode(INPUT_3, INPUT_PULLDOWN);
    pinMode(INPUT_4, INPUT_PULLDOWN);
    pinMode(INPUT_5, INPUT_PULLDOWN);

    // set outputs
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    // outputs for factory (simulated with LED´s)
    pinMode(CONVEYOR_BELT_1_OUT, OUTPUT);
    pinMode(CONVEYOR_BELT_2_OUT, OUTPUT);
    pinMode(CONVEYOR_BELT_3_OUT, OUTPUT);
    pinMode(CONVEYOR_BELT_4_OUT, OUTPUT);

    pinMode(SLIDE_MOTOR_1_OUT, OUTPUT);
    pinMode(SLIDE_MOTOR_2_OUT, OUTPUT);

    pinMode(TASK_MOTOR_1_OUT, OUTPUT);
    pinMode(TASK_MOTOR_2_OUT, OUTPUT);

    // set all pins with a "starting" value
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);

    digitalWrite(CONVEYOR_BELT_1_OUT, LOW);
    digitalWrite(CONVEYOR_BELT_2_OUT, LOW);
    digitalWrite(CONVEYOR_BELT_3_OUT, LOW);
    digitalWrite(CONVEYOR_BELT_4_OUT, LOW);

    digitalWrite(SLIDE_MOTOR_1_OUT, LOW);
    digitalWrite(SLIDE_MOTOR_2_OUT, LOW);

    digitalWrite(TASK_MOTOR_1_OUT, LOW);
    digitalWrite(TASK_MOTOR_2_OUT, LOW);
}

void readSensors()
{
    // measure the time difference between the "global time" and the objectTimestamp
    if (objectTimestamp > 0) {
        objTimeDiff = currentMilliSeconds - objectTimestamp;
    }
    if (slideMotorTimeStamp > 0) {
        slideMotorTimeDiff = currentMilliSeconds - slideMotorTimeStamp;
    }

    // set the ADC-resolution to xx-Bits
    analogReadResolution(12);
    int photoResistorValue1 = analogRead(PHOTO_RESISTOR_1);
    int photoResistorValue2 = analogRead(PHOTO_RESISTOR_2);

    // react to certain sensors
    if (photoResistorValue1 > 1300) {
        button1Status = true;
        output = "B1 stat\nchange:\nON";
        Serial.println("Photo_Sensor1 passed!");
    } else if (photoResistorValue2 > 1300) {
        button2Status = true;
        output = "B2 stat\nchange:\nON";
        Serial.println("Photo_Sensor2 passed!");
    }

    // read the inputs for factory control
    bool input1Digtital = digitalRead(INPUT_1);
    bool input2Digtital = digitalRead(INPUT_2);
    bool input3Digtital = digitalRead(INPUT_3);
    bool input4Digtital = digitalRead(INPUT_4);
    bool input5Digtital = digitalRead(INPUT_5);

    // the digital imputs are suppossed to simulate sensors!!!
    // reacting to inputs and "following opeartion/time"
    if (input1Digtital) {
        conveyorBelt1Status = 1;
        Serial.println("INPUT_1 digital: 1");
    }

    else if (input2Digtital) {
        Serial.println("INPUT_2 digital: 1");
        objectTimestamp = millis();
        Serial.println("Moving to slideMotor1 ...");
    }

    // after ... seconds switch from conveyorBelt to slideMotor
    // this if only if the conveyorBelt1 was already active
    else if (objTimeDiff > SWITCH_BELT_TO_SLIDE_TIME && conveyorBelt1Status == 1) {
        conveyorBelt1Status = 0;
        slideMotor1Status = 1;
        conveyorBelt2Status = 1;

        slideMotorTimeStamp = millis();
        Serial.println("Switching from slideMotor1 to conveyorBelt2");
    }

    // object in front first taskMotor
    else if (input3Digtital) {
        Serial.println("INPUT_3 digital: 1");
        conveyorBelt2Status = 0;
        taskMotor1Status = 1;

        // take the next objectTimestamp
        objectTimestamp = millis();
        Serial.println("conveyorBelt2 standstill, task1 working....");
    }

    // once the task is done, move to the next
    else if (objTimeDiff > TASK_TIME && taskMotor1Status == 1) {
        taskMotor1Status = 0;
        conveyorBelt2Status = 1;
        conveyorBelt3Status = 1;

        Serial.println("task1 finished, conveyorBelt2 & 3 moving");
    }

    // object in front of second taskMotor
    else if (input4Digtital) {
        Serial.println("INPUT_4 digital: 1");
        taskMotor2Status = 1;
        conveyorBelt2Status = 0;
        conveyorBelt3Status = 0;

        // take the next objectTimestamp
        objectTimestamp = millis();
        Serial.println("task2 is working ...");
    }

    // once the task is done, prepare to move to sliding motor
    else if (objTimeDiff > TASK_TIME && taskMotor2Status == 1) {
        taskMotor2Status = 0;
        conveyorBelt3Status = 1;

        // take the next objectTimestamp
        objectTimestamp = millis();
        Serial.println("Task2 finished, conveyorBelt3 moving to slide2");
    }

    // after ... seconds the object in now on the sliding motor
    // move to last conveyorBelt, CHECK IF BELT 2 IS STILL MOVING !!!
    else if (objTimeDiff > TASK_TIME && conveyorBelt3Status == 1 && conveyorBelt2Status != 1) {
        slideMotor2Status = 1;
        conveyorBelt3Status = 0;
        conveyorBelt4Status = 1;

        slideMotorTimeStamp = millis();
        Serial.println("switching from slidingMotor2 to conveyorBelt4");
    }

    // once the object arrived at the end, STOP
    else if (input5Digtital) {
        Serial.println("INPUT_5 digital: 1");
        conveyorBelt4Status = 0;
        // reset
        objectTimestamp = 0;
        objTimeDiff = 0;
        Serial.println("conveyorBelt4 standstill");
    }

    // move the slideMotors backward or stop if already backwards
    if (slideMotorTimeDiff > SLIDE_MOVE_TIME && (slideMotor1Status > 0 || slideMotor2Status > 0)) {
        if (slideMotor1Status == 1) {
            slideMotor1Status = 2;
            slideMotorTimeStamp = millis();
            Serial.println("slideMotor1 MOVE BACK!");
        } else if (slideMotor1Status == 2) {
            slideMotor1Status = 0;
            slideMotorTimeDiff = 0;
            slideMotorTimeStamp = 0;
            Serial.println("slideMotor1 STOP!");
        }

        if (slideMotor2Status == 1) {
            slideMotor2Status = 2;
            slideMotorTimeStamp = millis();
            Serial.println("slideMotor2 MOVE BACK!");
        } else if (slideMotor2Status == 2) {
            slideMotor2Status = 0;
            slideMotorTimeDiff = 0;
            slideMotorTimeStamp = 0;
            Serial.println("slideMotor2 STOP!");
        }
    }

    /* for debug
    Serial.println(photoResistorValue1);
    Serial.println(photoResistorValue2);
    */
}

// depending on the status, change the output
void writeOutputs()
{
    if (button1Status) {
        digitalWrite(LED1, HIGH);
    } else {
        digitalWrite(LED1, LOW);
    }

    if (button2Status) {
        digitalWrite(LED2, HIGH);
    } else {
        digitalWrite(LED2, LOW);
    }

    if (conveyorBelt1Status) {
        digitalWrite(CONVEYOR_BELT_1_OUT, HIGH);
    } else {
        digitalWrite(CONVEYOR_BELT_1_OUT, LOW);
    }

    if (conveyorBelt2Status) {
        digitalWrite(CONVEYOR_BELT_2_OUT, HIGH);
    } else {
        digitalWrite(CONVEYOR_BELT_2_OUT, LOW);
    }

    if (conveyorBelt3Status) {
        digitalWrite(CONVEYOR_BELT_3_OUT, HIGH);
    } else {
        digitalWrite(CONVEYOR_BELT_3_OUT, LOW);
    }

    if (conveyorBelt4Status) {
        digitalWrite(CONVEYOR_BELT_4_OUT, HIGH);
    } else {
        digitalWrite(CONVEYOR_BELT_4_OUT, LOW);
    }

    switch (slideMotor1Status) {
    case 0:
        digitalWrite(SLIDE_MOTOR_1_OUT, LOW);
        break;
    case 1:
        digitalWrite(SLIDE_MOTOR_1_OUT, HIGH);
        break;
    case 2:
        digitalWrite(SLIDE_MOTOR_1_OUT, HIGH);
    default:
        break;
    }

    switch (slideMotor2Status) {
    case 0:
        digitalWrite(SLIDE_MOTOR_2_OUT, LOW);
        break;
    case 1:
        digitalWrite(SLIDE_MOTOR_2_OUT, HIGH);
        break;
    case 2:
        digitalWrite(SLIDE_MOTOR_2_OUT, HIGH);
        break;
    default:
        break;
    }

    if (taskMotor1Status) {
        digitalWrite(TASK_MOTOR_1_OUT, HIGH);
    } else {
        digitalWrite(TASK_MOTOR_1_OUT, LOW);
    }

    if (taskMotor2Status) {
        digitalWrite(TASK_MOTOR_2_OUT, HIGH);
    } else {
        digitalWrite(TASK_MOTOR_2_OUT, LOW);
    }
}

void resetAllActuatorStatuses()
{
    conveyorBelt1Status = 0;
    conveyorBelt2Status = 0;
    conveyorBelt3Status = 0;
    conveyorBelt4Status = 0;

    slideMotor1Status = 0;
    slideMotor2Status = 0;

    taskMotor1Status = 0;
    taskMotor2Status = 0;
}