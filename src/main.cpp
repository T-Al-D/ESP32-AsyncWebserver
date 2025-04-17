#include "API.h"
#include "DisplayManager.h"
#include "../Controller/FactoryController/FactoryController.h"
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <Wire.h>

// GLOBAL VARIABLES
String output = "";
// unsigned long currentMilliSeconds = 0; // 0 to 4.294.967.295

// objects
FactoryController factory;

void setup()
{
    // set baudrate
    Serial.begin(115200);

    // setup objects
    factory.setupFactoryController();

    // activate the API
    startServer();

    // Initialize display
    initDisplay();
}

// put your main code here, to run repeatedly:
void loop()
{
    factory.loopFactoryController();

    // Serial.println(output);
    showOutput(output);
}
