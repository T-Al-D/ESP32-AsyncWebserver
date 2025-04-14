#include "API.h"
#include "DisplayManager.h"
#include "StatusControl.h"
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <Wire.h>

// GLOBAL VARIABLES
String output = "";
unsigned long currentMilliSeconds = 0; // 0 to 4.294.967.295

void setup()
{
    // set baudrate
    Serial.begin(115200);

    // activate the API
    startServer();

    // set the pins
    setPins();

    // Initialize display
    initDisplay();
}

// put your main code here, to run repeatedly:
void loop()
{
    // get current milliseconds since start
    currentMilliSeconds = millis();
    // Serial.println(currentMilliSeconds);

    readSensors();
    writeOutputs();

    // Serial.println(output);
    showOutput(output);
}
