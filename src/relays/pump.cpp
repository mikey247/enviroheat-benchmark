#include "pump.h"

PumpControl::PumpControl(int pumpRelayPin) : pumpRelayPin(pumpRelayPin) {}

void PumpControl::begin() {
  pinMode(pumpRelayPin, OUTPUT);
}

void PumpControl::turnOn() {
  digitalWrite(pumpRelayPin, HIGH);
}
void PumpControl::turnOnFor(int timeInSeconds) {
  digitalWrite(pumpRelayPin, HIGH);
  delay((timeInSeconds*1000));
  turnOff();
}

void PumpControl::turnOff() {
  digitalWrite(pumpRelayPin, LOW);
}