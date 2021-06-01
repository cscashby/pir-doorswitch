#include "Web.h"
#include "wwwroot.h"
#include "wwwmainjs.h"
#include "Network.h"

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
