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

/////////////////////////// FACTORY SIMULATION //////////////////////////
// 5 inputs for the factory simulation
extern const short INPUT_1;
extern const short INPUT_2;
extern const short INPUT_3;
extern const short INPUT_4;
extern const short INPUT_5;

// 4 conveyor belts, 2 Slidemotors, 2 taskmotors need to be moved (action)
// in THIS ORDER !
extern short conveyorBelt1Status;
extern short conveyorBelt2Status;
extern short conveyorBelt3Status;
extern short conveyorBelt4Status;

extern short slideMotor1Status;
extern short slideMotor2Status;

extern short taskMotor1Status;
extern short taskMotor2Status;
/////////////////////////// FACTORY SIMULATION //////////////////////////

void setPins();
void readSensors();
void writeOutputs();

#endif
