#include "temperature.h"

TemperatureSensor::TemperatureSensor(int DS18B20_PIN) : sensorPin(DS18B20_PIN), oneWire(DS18B20_PIN), sensors(&oneWire) {}

void TemperatureSensor::begin() {
  sensors.begin();
}

float TemperatureSensor::readTemperature() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

void TemperatureSensor::printTemperature() {
  float temperature = readTemperature();
  Serial.print("Temperature: ");
  Serial.println(temperature);
}
