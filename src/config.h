#ifndef Config_h
#define Config_h

#include <Arduino.h>

// ==== General setup
#define SERIAL_BAUD         460800
#define DEBUG

// ==== Network configuration
// WifiManager configuration
#define WM_CONNECT_TIMEOUT  10  // seconds
#define WM_PORTAL_TIMEOUT   30
#define WM_SSID             "pir-doorswitch"
#define WM_KEY              "doorswitch"

// I don't like 192 as default, so going with a 10. address instead (but a /24 to be nice)
#define WM_IP               IPAddress(192,168,222,1)
#define WM_GW               IPAddress(192,168,222,1)
#define WM_MASK             IPAddress(255,255,255,0)

#define WM_HOSTNAME         "pir-doorswitch"

// Uncomment the line below if you want to reset wifi config on boot
//#define WM_RESET_WIFI

#define NET_PORT            80

// ==== Debug stuff
#ifdef DEBUG
  #define DEBUG_PRINT(X) if (Serial) { \
    Serial.print("D "); \
    Serial.print(millis()); \
    Serial.print(": "); \
    Serial.print(X); \
    Serial.print(" ("); \
    Serial.print(__FUNCTION__); \
    Serial.print("() in "); \
    Serial.print(__FILE__); \
    Serial.print(':'); \
    Serial.print(__LINE__); \
    Serial.println(")"); }
  #define INFO
#else
  #define DEBUG_PRINT(X)
#endif
#ifdef INFO
  #define INFO_PRINT(X) if (Serial) { \
    Serial.print("I "); \
    Serial.print(millis()); \
    Serial.print(": "); \
    Serial.print(X); \
    Serial.print(" ("); \
    Serial.print(__FUNCTION__); \
    Serial.print("() in "); \
    Serial.print(__FILE__); \
    Serial.print(':'); \
    Serial.print(__LINE__); \
    Serial.println(")"); };
  #define WARN
#else
  #define INFO_PRINT(X)
#endif
#ifdef WARN
  #define WARN_PRINT(X) if (Serial) { \
    Serial.print("W "); \
    Serial.print(millis()); \
    Serial.print(": "); \
    Serial.print(X); \
    Serial.print(" ("); \
    Serial.print(__FUNCTION__); \
    Serial.print("() in "); \
    Serial.print(__FILE__); \
    Serial.print(':'); \
    Serial.print(__LINE__); \
    Serial.println(")"); };
#else
  #define WARN_PRINT(X)
#endif
#define ERROR_PRINT(X) if (Serial) { \
  Serial.print("E "); \
  Serial.print(millis()); \
  Serial.print(": "); \
  Serial.print(X); \
  Serial.print(" ("); \
  Serial.print(__FUNCTION__); \
  Serial.print("() in "); \
  Serial.print(__FILE__); \
  Serial.print(':'); \
  Serial.print(__LINE__); \
  Serial.println(")"); };
#endif