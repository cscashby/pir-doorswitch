#ifndef Monitor_h
#define Monitor_h

#include "config.h"
#include "Network.h"
#include <Arduino.h>
#include <Ticker.h> // This is the ESP32 ticker library which uses the ESP32 built in timer, so no interrupts or loop() requirement

class Monitor {
  public:
    Monitor();
    void begin();
    void loop();

    static Monitor& get() {
      static Monitor instance;
      return instance;
    }        
  private:
    Network net;
  
    static void blink(int pin);
    static void tick();
};

#endif // Monitor_h