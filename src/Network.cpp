#include "Network.h"
#include "Web.h"

AsyncWebServer *Network::server = new AsyncWebServer(NET_PORT);

Network::Network() {
  
}

AsyncWebServer Network::getServer() {
  return *server;
}

void configModeCallback(AsyncWiFiManager *myWiFiManager) {
  DEBUG_PRINT("Entered config mode");
}

void Network::begin() {
  dns = new DNSServer();
  wifiManager = new AsyncWiFiManager(server, dns);

  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP    
  #ifdef DEBUG
    Serial.setDebugOutput(true);
    wifiManager->setDebugOutput(true);
  #else
    wifiManager->setDebugOutput(false);
  #endif

  #ifdef WM_RESET_WIFI
    wifiManager->resetSettings();
  #endif

  wifiManager->setAPStaticIPConfig(WM_IP, WM_GW, WM_MASK);
  wifiManager->setConnectTimeout(WM_CONNECT_TIMEOUT);
  wifiManager->setConfigPortalTimeout(WM_PORTAL_TIMEOUT);
  wifiManager->setAPCallback(configModeCallback);
  wifiManager->startConfigPortalModeless(WM_SSID, WM_KEY);
}

void Network::loop() {  
  // Check to see if we're connected
  if( WiFi.status() == WL_CONNECTED ) {
    lastConnected = millis();
    // If we don't know we're connected then
    if( !connected ) {
      // set our flag to say we're online
      connected = true;
      // we're connected so we disable our AP by setting ourselves to station mode
      WiFi.mode(WIFI_STA);
      // register web actions (server will have been reset)
      Web::registerActions(server);
      #ifdef DEBUG
        char debug[100];
        sprintf(debug, "Connected to wifi since %ld", lastConnected);
        DEBUG_PRINT((debug));
      #endif
    }
  } else {
    lastDisconnected = millis();
    // If we don't know we're connected then debug and set our flag
    if( connected ) { 
      connected = false;
      #ifdef DEBUG
        char debug[100];
        sprintf(debug, "Disconnected from wifi since %ld", lastDisconnected);
        DEBUG_PRINT((debug));
      #endif
    }
  }

  wifiManager->loop();
}

void Network::reset() {
  ERROR_PRINT("Resetting WiFi settings");
  wifiManager->resetSettings();
  ERROR_PRINT("Restarting device");
  ESP.restart();
}
