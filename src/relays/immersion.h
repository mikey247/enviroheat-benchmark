#ifndef IMMERSION_SENSOR_H
#define IMMERSION_SENSOR_H

#include <Arduino.h>

class ImmersionControl {
public:
  ImmersionControl(int immersionRelayPin);
  void begin();
  void turnOn();
  void turnOff();
  

private:
  int immersionRelayPin;
};

#endif