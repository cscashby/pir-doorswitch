#ifndef Web_h
#define Web_h
#include <ESPAsyncWebServer.h>
#include "Network.h"
#include "config.h"

class Web {
  public:
    Web();
    void begin();
    void loop();

    static void registerActions(AsyncWebServer *server);

    static Web& get() {
      static Web instance;
      return instance;
    }        
};

#endif // Web_h
