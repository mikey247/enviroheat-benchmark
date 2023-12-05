#ifndef VALVE_CONTROL_H
#define VALVE _CONTROL_H

#include <Arduino.h>

class ValveControl {
public:
  ValveControl(int valveControlPin);
  void begin();
  void turnOn();
  void turnOnFor(int timeInSeconds);
  void turnOff();
  bool getValveStatus();

private:
  int valveControlPin;
  bool isValveOn;
};

#endif