#include "immersion.h"

ImmersionControl::ImmersionControl(int immersionRelayPin) : immersionRelayPin(immersionRelayPin) {
  
}

void ImmersionControl::begin() {
  pinMode(immersionRelayPin, OUTPUT);
}

void ImmersionControl::turnOn() {
  digitalWrite(immersionRelayPin, HIGH);
}

void ImmersionControl::turnOnFor(int timeInSeconds){
 digitalWrite(immersionRelayPin, HIGH);
  delay((timeInSeconds*1000));
  turnOff();
}

void ImmersionControl::turnOff() {
  digitalWrite(immersionRelayPin, LOW);
}