// pre processing directive
#ifndef GPIO_DEFINITIONS_H
#define GPIO_DEFINITIONS_H

#include <Arduino.h>

// declaration for external pin variables
extern const short LED1;
extern const short LED2;

extern const short PHOTO_RESISTOR_1;
extern const short PHOTO_RESISTOR_2;

// statuses are important, to keep track of pin infor
// example: motor or LED on/off
extern bool button1status;
extern bool button2status;

void setPins();
void readSensors();
void writeOutputs();

#endif
