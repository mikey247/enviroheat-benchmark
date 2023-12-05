#include "temperature.h"
#include "constants.h"

TemperatureSensor::TemperatureSensor(int DS18B20_PIN) :
 sensorPin(DS18B20_PIN), oneWire(DS18B20_PIN), sensors(&oneWire) {}

void TemperatureSensor::begin() {
  sensors.begin();
}

float TemperatureSensor::readTemperature() {
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  Serial.print(TemperatureField+String(temp));
  return temp;
}

void TemperatureSensor::printTemperature() {
  float temperature = readTemperature();
  Serial.print("Temperature: ");
  Serial.println(temperature);
}
