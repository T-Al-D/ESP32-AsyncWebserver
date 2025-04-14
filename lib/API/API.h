// pre processing directive
#ifndef WEBSERVER_ROUTES_H
#define WEBSERVER_ROUTES_H

#include "../Controller/FactoryController/FactoryController.h"
#include "HTML.h"
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

void startServer();
void setupAsyncWebServer(AsyncWebServer& server);

void handleOnConnect(AsyncWebServerRequest* request);
void handleReset(AsyncWebServerRequest* request);
void handleRefereshStatuses(AsyncWebServerRequest* request);

void handleInputText(AsyncWebServerRequest* request);
void handleNotFound(AsyncWebServerRequest* request);

#endif