#include "Monitor.h"
#include "Web.h"

Monitor::Monitor() {
}

Ticker statusTicker;
int statusCounter = 0;
int wifiCounter = 0;
#ifdef DEBUG
  int timeCounter = 0;
#endif

void Monitor::blink(int pin) {
  digitalWrite(pin, !digitalRead(pin));
}

void Monitor::tick() {
  wifiCounter++;
#ifdef DEBUG
  timeCounter++;
#endif

  int c = (Network::get().isConnected() ? MONITOR_OKCOUNTER : MONITOR_WAITCOUNTER);
  if( wifiCounter > c ) {
    wifiCounter = 0;
    blink(PIN_WIFI_LED);
  }

 #ifdef DEBUG
  if( timeCounter > MONITOR_TIME ) {
    timeCounter = 0;
    DEBUG_PRINT(Network::get().getNTPClient().getFormattedTime());
  }
#endif
}

void Monitor::begin() {
  // ===== Setup I/O
  pinMode(PIN_STATUS_LED, OUTPUT);
  pinMode(PIN_WIFI_LED, OUTPUT);

  // Status LED is 'OK' is on (HIGH), off (LOW) is something wrong
  digitalWrite(PIN_STATUS_LED, HIGH);
  digitalWrite(PIN_WIFI_LED, HIGH);

  // Start the ticker
  statusTicker.attach_ms(MONITOR_TICKER, Monitor::tick);
}

void Monitor::loop() {
  // We'll add some to this with logical and but for now just network connectivity
  bool ok = Network::get().isConnected();
  
  digitalWrite(PIN_STATUS_LED, ok);
}
