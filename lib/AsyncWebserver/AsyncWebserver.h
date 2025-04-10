// pre processing directive
#ifndef WEBSERVER_ROUTES_H
#define WEBSERVER_ROUTES_H

#include <ESPAsyncWebServer.h>

void setupAsyncWebServer(AsyncWebServer& server);

void handleOnConnect(AsyncWebServerRequest* request);
void handleButtonToggle(AsyncWebServerRequest* request, int buttonNumber, bool newStatus);
void handleReset(AsyncWebServerRequest* request);
void handleRefereshStatuses(AsyncWebServerRequest* request);

void handleInputText(AsyncWebServerRequest* request);
void handleNotFound(AsyncWebServerRequest* request);

#endif