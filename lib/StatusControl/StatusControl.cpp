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

bool button1status = false;
bool button2status = false;
extern String output;

void setPins()
{
    // set output
    pinMode(PHOTO_RESISTOR_1, INPUT);
    pinMode(PHOTO_RESISTOR_2, INPUT);

    // set output
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
        button1status = true;
        output = "B1 stat\nchange:\nON";
        Serial.println("Photo_Sensor1 passed!");
    } else if (photoResistorValue2 > 1300) {
        button2status = true;
        output = "B2 stat\nchange:\nON";
        Serial.println("Photo_Sensor2 passed!");
    }

    // for debug
    Serial.println(photoResistorValue1);
    Serial.println(photoResistorValue2);
}

// depending on the status, change the output
void writeOutputs()
{
    if (button1status) {
        digitalWrite(LED1, HIGH);
    } else {
        digitalWrite(LED1, LOW);
    }

    if (button2status) {
        digitalWrite(LED2, HIGH);
    } else {
        digitalWrite(LED2, LOW);
    }
}