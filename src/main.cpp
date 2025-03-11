#include "AsyncWebserver.h"
#include "Displaymanager.h"
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <Wire.h>

// GLOBAL VARIABLES
String output = "";
bool button1status = false;
bool button2status = false;

// Network credentials
const char* SSID = "ESP32-Experiment";
const char* PASSWORD = "12345678";

AsyncWebServer server(80);

/* put IP Address details */
IPAddress local_ip(192, 168, 4, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void setup()
{
    Serial.begin(115200);

    // Setup Wi-Fi
    WiFi.softAP(SSID, PASSWORD);
    WiFi.config(local_ip, gateway, subnet);

    // Initialize display
    initDisplay();

    // Setup webserver routes
    setupAsyncWebServer(server);

    // Start the server
    server.begin();
}

// put your main code here, to run repeatedly:
void loop()
{
    Serial.println(output);
    showOutput(output);
}
