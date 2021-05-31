#include <Arduino.h>
#include <TinyPICO.h>

TinyPICO tp = TinyPICO();

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  tp.DotStar_CycleColor(5);
}