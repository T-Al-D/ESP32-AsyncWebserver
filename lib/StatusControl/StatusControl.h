// pre processing directive
#ifndef GPIO_DEFINITIONS_H
#define GPIO_DEFINITIONS_H

#include <Arduino.h>

// declaration for external pin variables
extern const short LED1;
extern const short LED2;

extern const short PHOTO_RESISTOR_1;
extern const short PHOTO_RESISTOR_2;

// statuses are important, to keep track of pin information
// example: motor or LED on/off
extern bool button1Status;
extern bool button2Status;

void setPins();
void readSensors();
void writeOutputs();

#endif
