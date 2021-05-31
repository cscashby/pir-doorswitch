#ifndef Network_h
#define Network_h

#ifdef ESP8266
  #include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h>
#endif

#include <ESPAsyncWebServer.h>     //Local WebServer used to serve the configuration portal
#include <ESPAsyncWiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include "config.h"

class Network {
  public:
    Network();
    void begin();
    void loop();

    bool isConnected() { return connected; }
    bool isPortalActive() { return portalActive; }

    static Network& get() {
      static Network instance;
      return instance;
    }                
  private:
    bool portalActive = false;
    bool connected = false;

    long lastConnected = -1; // millis() when device was last online
};

#endif // Network_h
