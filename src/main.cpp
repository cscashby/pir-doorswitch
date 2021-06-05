#include <Arduino.h>

#include "config.h"       // My configuration parameters, etc.

#include "Network.h"
#include "Web.h"
#include "Monitor.h"

#include <Ticker.h>

// We're using singletons here as the classes need to use each others' methods
static Network& net = Network::get();
static Web& web = Web::get();
static Monitor& mon = Monitor::get();

Ticker PIRTicker;
bool enabled = false;
int pirState, switchState = HIGH;
int tickerCounter = 0;

void setupLEDstatus() {
  if( enabled ) {
    mon.statusSlowFlash();
  } else {
    mon.statusOn();
  }
  #ifdef DEBUG
    mon.additionalStatus = String("Lock ") + String(enabled ? "active" : "inactive");
  #endif
}

void tick() {
  tickerCounter++;
  // If we have no network we defualt to inactivate
  if( !Network::get().isConnected() ) {
    enabled = false;
    mon.statusOff();
  } else {
    setupLEDstatus();
    int checkSwitch = digitalRead(PIN_SWITCH_INPUT);
    if (checkSwitch != switchState) {
      switchState = checkSwitch;
      DEBUG_PRINT(switchState == LOW ? "Switch pressed" : "Switch released");
      // We only deal with released switch events which come after pressed
      if (switchState == HIGH) {
        enabled = !enabled;
      }
    }

    if (enabled && tickerCounter > PIR_TICKER_COUNTER) {
      tickerCounter = 0;
      int checkState = digitalRead(PIN_PIR_INPUT);
      if (checkState != pirState) {
        pirState = checkState;
        DEBUG_PRINT(pirState == LOW ? "PIR inactive" : "PIR active");
        // 'press' door button if PIR has gone active (PIN_RELAY_OUTPUT)
        digitalWrite(PIN_RELAY_OUTPUT, !pirState);
        if (pirState == LOW) {
          setupLEDstatus();
        } else {
          mon.statusFastFlash();
        }
      }
    }
  }
}

void setup() {
  #ifdef DEBUG
    Serial.begin(SERIAL_BAUD);
    while(!Serial) { delay(100); }
  #endif
  
  net.begin();
  web.begin();
  mon.begin();

  pinMode(PIN_SWITCH_INPUT, INPUT_PULLUP);
  pinMode(PIN_PIR_INPUT, INPUT);
  pinMode(PIN_RELAY_OUTPUT, OUTPUT);
  pirState = digitalRead(PIN_PIR_INPUT);
  digitalWrite(PIN_RELAY_OUTPUT, HIGH);

  // Start the ticker
  PIRTicker.attach_ms(MAIN_TICKER, tick);
}

void loop() {
  net.loop();
  web.loop();
  mon.loop();
}
