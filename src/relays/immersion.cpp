#include "immersion.h"

ImmersionControl::ImmersionControl(int immersionRelayPin) : immersionRelayPin(immersionRelayPin) {}

void ImmersionControl::begin() {
  pinMode(immersionRelayPin, OUTPUT);
}

void ImmersionControl::turnOn() {
  digitalWrite(immersionRelayPin, HIGH);
}

void ImmersionControl::turnOff() {
  digitalWrite(immersionRelayPin, LOW);
}