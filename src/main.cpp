#include <Arduino.h>

#include "config.h"       // My configuration parameters, etc.

#include "Network.h"
#include "Web.h"
#include "Monitor.h"

// We're using singletons here as the classes need to use each others' methods
static Network& net = Network::get();
static Web& web = Web::get();
static Monitor& mon = Monitor::get();

void setup() {
  #ifdef DEBUG
    Serial.begin(SERIAL_BAUD);
    while(!Serial) { delay(100); }
  #endif
  
  net.begin();
  web.begin();
  mon.begin();
}

void loop() {
  net.loop();
  web.loop();
  mon.loop();
}
