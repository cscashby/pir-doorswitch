#ifndef Monitor_h
#define Monitor_h

#include "config.h"
#include "Network.h"
#include <Arduino.h>
#include <Ticker.h> // This is the ESP32 ticker library which uses the ESP32 built in timer, so no interrupts or loop() requirement

// This class has a bit of a static / non static confusion that I need to clean up
class Monitor {
  public:
    Monitor();
    void begin();
    void loop();

    void statusFastFlash();
    void statusSlowFlash();
    void statusOn();
    void statusOff();

  #ifdef DEBUG
    String additionalStatus;
  #endif

    static Monitor& get() {
      static Monitor instance;
      return instance;
    }        
  private:
    Network net;
  
    static void blink(int pin);
    static void tick();

    enum StatusState { STATUS_FASTFLASH, STATUS_SLOWFLASH, STATUS_ON, STATUS_OFF };
    StatusState statusFlashState;
};

#endif // Monitor_h
