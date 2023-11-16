#ifndef PUMP_CONTROL_H
#define PUMP_CONTROL_H

#include <Arduino.h>

class PumpControl {
public:
  PumpControl(int pumpRelayPin);
  void begin();
  void turnOn();
  void turnOnFor(int timeInSeconds);
  void turnOff();

private:
  int pumpRelayPin;
};

#endif