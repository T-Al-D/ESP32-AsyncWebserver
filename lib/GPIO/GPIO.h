// pre processing directive
#ifndef GPIO_DEFINITIONS_H
#define GPIO_DEFINITIONS_H

#include <Arduino.h>

// declaration for external pin variables
extern const short LED1;
extern const short LED2;

extern const short PHOTO_RESISTOR_1;
extern const short PHOTO_RESISTOR_2;

void setPins();
void readSensors();
void writeOutputs();

#endif
