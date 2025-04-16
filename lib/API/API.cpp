#include "API.h"

// network credentials
const char* SSID = "ESP32-Experiment";
const char* PASSWORD = "12345678";

AsyncWebServer server(80);

/* put IP Address details */
IPAddress local_ip(192, 168, 4, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// import from main.cpp
extern String output;
extern FactoryController factory;

void startServer()
{
    // setup Wi-Fi
    WiFi.softAP(SSID, PASSWORD);
    WiFi.config(local_ip, gateway, subnet);

    // setup webserver routes
    setupAsyncWebServer(server);

    // start the APIs
    server.begin();
}

void setupAsyncWebServer(AsyncWebServer& server)
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        handleOnConnect(request);
    });

    // reset everything
    server.on("/reset", HTTP_GET, [](AsyncWebServerRequest* request) {
        handleReset(request);
    });

    // define the "status-page" for the javascript refesh
    server.on("/refreshStatuses", HTTP_GET, [](AsyncWebServerRequest* request) {
        handleRefereshStatuses(request);
    });

    server.on("/inputText", HTTP_GET, handleInputText);
    // in case no route was found
    server.onNotFound(handleNotFound);

    // debug current IP Adress
    output = "Webserver\ninit!\n" + WiFi.softAPIP().toString();
}

void handleOnConnect(AsyncWebServerRequest* request)
{
    // Serial.println("Received request on /");
    output = "HTTP up!\nActuators off ";
    request->send(200, "text/html", SendHTML());
}

void handleReset(AsyncWebServerRequest* request)
{
    factory.reset();
    output = "RESET ALL!";
    request->send(200, "text/html", SendHTML());
}

void handleRefereshStatuses(AsyncWebServerRequest* request)
{
    request->send(200, "text/html", SendHTML());
}

void handleInputText(AsyncWebServerRequest* request)
{
    String otherInfo = "";
    if (request->hasParam("param")) {
        otherInfo = request->getParam("param")->value();
    }
    output = "Text :\n" + otherInfo;
    request->send(200, "text/html", SendHTML());
}

void handleNotFound(AsyncWebServerRequest* request)
{
    output = "Not Found!\nError 404";
    request->send(404, "text/plain");
}