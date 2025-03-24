// pre processing directive
#ifndef GPIO_DEFINITIONS_H
#define GPIO_DEFINITIONS_H

#include <Arduino.h>

// declaration for external pin variables
extern const short LED1;
extern const short LED2;

void setPins();
void checkForEmergecy();

#endif
