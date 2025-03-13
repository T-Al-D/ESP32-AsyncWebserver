#include "AsyncWebserver.h"
#include "GPIO.h"
#include "HTML.h"
#include <Arduino.h>
#include <WiFi.h>

// from main.cpp
extern bool button1status;
extern bool button2status;
extern String output;
extern String SendHTML(bool, bool, String);

void setupAsyncWebServer(AsyncWebServer& server)
{
    server.on("/", HTTP_GET, handleOnConnect);
    server.on("/button1on", HTTP_GET, [](AsyncWebServerRequest* request) {
        handleButtonToggle(request, 1, true);
    });
    server.on("/button1off", HTTP_GET, [](AsyncWebServerRequest* request) {
        handleButtonToggle(request, 1, false);
    });
    server.on("/button2on", HTTP_GET, [](AsyncWebServerRequest* request) {
        handleButtonToggle(request, 2, true);
    });
    server.on("/button2off", HTTP_GET, [](AsyncWebServerRequest* request) {
        handleButtonToggle(request, 2, false);
    });
    server.on("/inputText", HTTP_GET, handleInputText);

    server.onNotFound(handleNotFound);

    // debug current IP Adress
    output = "Webserver\ninit!\n" + WiFi.softAPIP().toString();
}

void handleOnConnect(AsyncWebServerRequest* request)
{
    Serial.println("Received request on /");
    button1status = false;
    button2status = false;
    output = "HTTP up!\nButton1 & Button2: OFF ";
    request->send(200, "text/html", SendHTML(button1status, button2status, output));
}

void handleButtonToggle(AsyncWebServerRequest* request, int buttonNumber, bool newStatus)
{
    // depending wether current status has to be set to LOW or High
    uint8_t statusValue = newStatus ? HIGH : LOW;
    String currentStatus = String(newStatus ? "ON" : "OFF");
    String pressedButton = "";

    // switch depending which button was pressed
    switch (buttonNumber) {
    case 1:
        button1status = newStatus;
        digitalWrite(LED1, statusValue);
        pressedButton = "Button1";
        break;
    case 2:
        button2status = newStatus;
        // currently no pin set
        pressedButton = "Button2";
        break;

    default:
        pressedButton = "ERROR";
        break;
    }

    // output string and sending request
    output = pressedButton + "\nStatus\nchange:" + currentStatus;
    request->send(200, "text/html", SendHTML(button1status, button2status, output));
}

void handleInputText(AsyncWebServerRequest* request)
{
    String otherInfo = "";
    if (request->hasParam("param")) {
        otherInfo = request->getParam("param")->value();
    }
    output = "Text :\n" + otherInfo;
    request->send(200, "text/html", SendHTML(button1status, button2status, otherInfo));
}

void handleNotFound(AsyncWebServerRequest* request)
{
    output = "Not Found!\nError 404";
    request->send(404, "text/plain", output);
}