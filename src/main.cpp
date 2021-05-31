#include <Arduino.h>

#include "config.h"       // My configuration parameters, etc.
#include "Network.h"

// We're using singletons here as the classes need to use each others' methods
static Network& net = Network::get();

void setup() {
  #ifdef DEBUG
    Serial.begin(SERIAL_BAUD);
    while(!Serial) { delay(100); }
  #endif
  
  net.begin();
}

void loop() {
  net.loop();
}
