#include "pump.h"

PumpControl::PumpControl(int pumpRelayPin) : pumpRelayPin(pumpRelayPin) {}

void PumpControl::begin() {
  pinMode(pumpRelayPin, OUTPUT);
}

void PumpControl::turnOn() {
  digitalWrite(pumpRelayPin, HIGH);
}

void PumpControl::turnOff() {
  digitalWrite(pumpRelayPin, LOW);
}