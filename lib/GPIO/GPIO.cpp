#include "GPIO.h"

// define the pins
const short LED1 = 2;

void setPins()
{
    // set output
    pinMode(LED1, OUTPUT);

    // set all pins with a "starting" value
    digitalWrite(LED1, LOW);
}