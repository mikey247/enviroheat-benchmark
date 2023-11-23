#ifndef IMMERSION_SENSOR_H
#define IMMERSION_SENSOR_H

#include <Arduino.h>

class ImmersionControl {
public:
  ImmersionControl(int immersionRelayPin);
  void begin();
  void turnOn();
  void turnOnFor(int timeInSeconds);
  void turnOff();
  bool getImmersionState();
  

private:
  int immersionRelayPin;
  bool isImmersionOn; 
};

#endif