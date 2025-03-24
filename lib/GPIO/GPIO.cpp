#include "GPIO.h"

// define the pins
const short LED1 = 1;
const short LED2 = 2;

const short EMERGECY_STOP = 44;

void setPins()
{
    // set output
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(EMERGECY_STOP, INPUT_PULLUP);

    // set all pins with a "starting" value
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(EMERGECY_STOP, LOW);
}