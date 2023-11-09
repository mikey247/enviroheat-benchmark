#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <OneWire.h>
#include <DallasTemperature.h>

class TemperatureSensor {
public:
  TemperatureSensor(int DS18B20_PIN);
  void begin();
  float readTemperature();
  void printTemperature();

private:
  int sensorPin;
  OneWire oneWire;
  DallasTemperature sensors;
};

#endif