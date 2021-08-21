#ifndef Config_h
#define Config_h

#include <Arduino.h>
#include <Timezone.h>

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

// ==== Monitor configuration
// Pins (GPIO numbers)
#define PIN_STATUS_LED      16  // D0
#define PIN_WIFI_LED        2   // Builtin ESP-12 LED

// Monitor timings
#define MONITOR_TICKER              10   // ms base timer
#define MONITOR_TIMECOUNTER         500 // Counts of ticker to debug print time
#define MONITOR_NET_OKCOUNTER       200  // Counts of ticker to identify OK
#define MONITOR_NET_WAITCOUNTER     10   // Counts of ticker to identify 'network not connected'
#define MONITOR_STATUS_SLOWCOUNTER  100  // Counts of ticker to identify OK
#define MONITOR_STATUS_FASTCOUNTER  2    // Counts of ticker to identify activity

// PIR timings
#define MAIN_TICKER                  10   // ms timer
#define PIR_TICKER_COUNTER          100  // stabilisation time for PIR

// ==== Main configuration
// Pins (GPIO numbers) for door control
#define PIN_RELAY_OUTPUT    5   // D1
#define PIN_PIR_INPUT       4   // D2
#define PIN_SWITCH_INPUT    0   // D3

// Auto unlock automatic disable time - default and current setting
#define DEFAULT_DISABLE_TIME        "22:00:00"

// Localization settings
// United Kingdom (London, Belfast)
#define BST                 (TimeChangeRule){"BST", Last, Sun, Mar, 1, 60}  // British Summer Time
#define GMT                 (TimeChangeRule){"GMT", Last, Sun, Mar, 1, 60}  // Standard Time
#define TIMEZONE            Timezone(BST, GMT)

// ==== Debug stuff (with NTP time)
#ifdef DEBUG
  // use millis() if no NTP
  #define DEBUG_PRINT(X) if (Serial) { \
    Serial.print("D "); \
    Serial.print(Network::get().getNTPClient().getFormattedTime()); \
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
  // use millis() if no NTP
  #define INFO_PRINT(X) if (Serial) { \
    Serial.print("I "); \
    Serial.print(Network::get().getNTPClient().getFormattedTime()); \
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
  // use millis() if no NTP
  #define WARN_PRINT(X) if (Serial) { \
    Serial.print("W "); \
    Serial.print(Network::get().getNTPClient().getFormattedTime()); \
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
// use millis() if no NTP
#define ERROR_PRINT(X) if (Serial) { \
  Serial.print("E "); \
  Serial.print(Network::get().getNTPClient().getFormattedTime()); \
  Serial.print(": "); \
  Serial.print(X); \
  Serial.print(" ("); \
  Serial.print(__FUNCTION__); \
  Serial.print("() in "); \
  Serial.print(__FILE__); \
  Serial.print(':'); \
  Serial.print(__LINE__); \
  Serial.println(")"); };

#endif // Config_h
