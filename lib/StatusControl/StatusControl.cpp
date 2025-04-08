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

short conveyorBelt1Status = false;
short conveyorBelt2Status = false;
short conveyorBelt3Status = false;
short conveyorBelt4Status = false;

short slideMotor1Status = false;
short slideMotor2Status = false;

short taskMotor1Status = false;
short taskMotor2Status = false;
/////////////////////////// FACTORY SIMULATION //////////////////////////

// "import" global variables
extern String output;

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

    // set all pins with a "starting" value
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
}

void readSensors()
{
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

    // react to inputs
    if (input1Digtital) {
        Serial.println("INPUT_1 digital: " + String(input1Digtital));
        Serial.println("--------------");
    }
    if (input2Digtital) {
        Serial.println("INPUT_2 digital: " + String(input2Digtital));
        Serial.println("--------------");
    }
    if (input3Digtital) {
        Serial.println("INPUT_3 digital: " + String(input3Digtital));
        Serial.println("--------------");
    }
    if (input4Digtital) {
        Serial.println("INPUT_4 digital: " + String(input4Digtital));
        Serial.println("--------------");
    }
    if (input5Digtital) {
        Serial.println("INPUT_5 digital: " + String(input5Digtital));
        Serial.println("--------------");
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
}