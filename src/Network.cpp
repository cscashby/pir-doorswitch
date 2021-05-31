#include "Network.h"

Network::Network() {
}

void Network::begin() {
  // ===== Setup Wifi
  AsyncWebServer server(NET_PORT);
  DNSServer dns;

  AsyncWiFiManager wifiManager(&server,&dns);

  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP    
  #ifdef DEBUG
    Serial.setDebugOutput(true);
    wifiManager.setDebugOutput(true);
  #else
    wifiManager.setDebugOutput(false);
  #endif

  #ifdef WM_RESET_WIFI
    wifiManager.resetSettings();
  #endif

  wifiManager.setAPStaticIPConfig(WM_IP, WM_GW, WM_MASK);
  wifiManager.setConnectTimeout(WM_CONNECT_TIMEOUT);
  wifiManager.setConfigPortalTimeout(WM_PORTAL_TIMEOUT);

  // Try to connect if we have been setup
  if( wifiManager.autoConnect(WM_SSID, WM_KEY) ) {
    INFO_PRINT(("Wifi connected"));
    lastConnected = millis();
  }
}

void Network::loop() {  
  // Check to see if we're connected
  if( WiFi.status() == WL_CONNECTED ) {
    lastConnected = millis();
    // If we don't know we're connected then debug and set our flag
    if( !connected ) { 
      connected = true;
      #ifdef DEBUG
        char debug[100];
        sprintf(debug, "Connected to wifi since %d", lastConnected);
        DEBUG_PRINT((debug));
      #endif
    }
  }
}
