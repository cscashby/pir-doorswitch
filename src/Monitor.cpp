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

void Monitor::statusFastFlash() { statusFlashState = STATUS_FASTFLASH; }
void Monitor::statusSlowFlash() { statusFlashState = STATUS_SLOWFLASH; }
void Monitor::statusOn() { statusFlashState = STATUS_ON; }
void Monitor::statusOff() { statusFlashState = STATUS_OFF; }

void Monitor::blink(int pin) {
  digitalWrite(pin, !digitalRead(pin));
}

void Monitor::tick() {
  wifiCounter++;
  statusCounter++;
#ifdef DEBUG
  timeCounter++;
#endif

  int c = (Network::get().isConnected() ? MONITOR_NET_OKCOUNTER : MONITOR_NET_WAITCOUNTER);
  if( wifiCounter > c ) {
    wifiCounter = 0;
    blink(PIN_WIFI_LED);
  }
  if( Network::get().isConnected() ) {
    switch( Monitor::get().statusFlashState ) {
    case STATUS_FASTFLASH:
      if( statusCounter > MONITOR_STATUS_FASTCOUNTER ) {
        statusCounter = 0;
        blink(PIN_STATUS_LED);
      }
      break;
    case STATUS_SLOWFLASH:
      if( statusCounter > MONITOR_STATUS_SLOWCOUNTER ) {
        statusCounter = 0;
        blink(PIN_STATUS_LED);
      }
      break;
    case STATUS_ON:
      statusCounter = 0;
      digitalWrite(PIN_STATUS_LED, HIGH);
      break;
    default:
      statusCounter = 0;
      digitalWrite(PIN_STATUS_LED, LOW);
    }
  } else {
    statusCounter = 0;
    digitalWrite(PIN_STATUS_LED, LOW);
  }

#ifdef DEBUG
  if( timeCounter > MONITOR_TIMECOUNTER ) {
    timeCounter = 0;
    String msg = String();
    if( Monitor::get().additionalStatus.length() > 0 )
      msg += Monitor::get().additionalStatus + "\n\t\t";
    msg += Network::get().getNTPClient().getFormattedTime();
    DEBUG_PRINT(msg);
  }
#endif
}

void Monitor::begin() {
  // ===== Setup I/O
  pinMode(PIN_STATUS_LED, OUTPUT);
  pinMode(PIN_WIFI_LED, OUTPUT);

  statusOn();
  digitalWrite(PIN_WIFI_LED, HIGH);

  // Start the ticker
  statusTicker.attach_ms(MONITOR_TICKER, Monitor::tick);
}

void Monitor::loop() {
}
