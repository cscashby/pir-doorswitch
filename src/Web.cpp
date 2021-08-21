#include "Web.h"
#include "wwwroot.h"
#include "wwwmainjs.h"
#include "Network.h"
#include "Monitor.h"

Web::Web() {
}

void Web::begin() {

}

void Web::loop() {

}

//static
void Web::registerActions(AsyncWebServer *server) {
  DEBUG_PRINT(("Registering my server actions"));
  // ===== Setup web server
  server->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", WEBPAGE_ROOT);
  });
  server->on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", MAINJS_ROOT);
  });
  // Settings
  server->on("/saveSettings", HTTP_POST, [](AsyncWebServerRequest *request) {
    DEBUG_PRINT("/saveSettings called");
    //Check if POST parameter exists
    if(request->hasParam("disableTime", true)) {
      AsyncWebParameter *p = request->getParam("disableTime", true);
      DEBUG_PRINT("Disable time set: " + p->value());
      Monitor::get().settingAutoDisableTime = p->value();
      request->send(200, "text/plain", "Saved");
    } else {
      request->send(400, "text/plain", "No disableTime parameter found");
    }
  });
  // Status codes
  // - device time
  server->on("/getTime", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", Network::get().getNTPClient().getFormattedTime());
  });
  // - last unlock time
  server->on("/getLastUnlockedTime", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", Monitor::get().lastUnlockedTime);
  });
  // - auto unlock status
  server->on("/getStatus", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", Monitor::get().additionalStatus);
  });
  // - last set time
  server->on("/getLastSetTime", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", Monitor::get().lastSetTime);
  });
  // - auto unlock disable time
  server->on("/getAutoDisableTime", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", Monitor::get().settingAutoDisableTime);
  });
  // Couple of useful reset capabilities
  // - reset wifi
  server->on("/reset", HTTP_GET, [](AsyncWebServerRequest *request) {
    ERROR_PRINT(("Reset requested"));
    // TODO: Core dumps
    Network::get().reset();
    ESP.restart();
  });
  // - reboot (no reset)
  server->on("/reboot", HTTP_GET, [](AsyncWebServerRequest *request) {
    ERROR_PRINT(("Reboot requested"));
    request->send(200, "text/plain", "Rebooting");
    ESP.restart();
  });
  server->onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");    
  });
}
