#include "pump.h"

PumpControl::PumpControl(int pumpRelayPin) : pumpRelayPin(pumpRelayPin), isPumpOn(false) {}

void PumpControl::begin() {
  pinMode(pumpRelayPin, OUTPUT);
}

void PumpControl::turnOn() {
  digitalWrite(pumpRelayPin, HIGH);
   isPumpOn = true;
   Serial.println("⛽PUMP IS ON");
}
void PumpControl::turnOnFor(int timeInSeconds) {
  digitalWrite(pumpRelayPin, HIGH);
  Serial.print("⛽PUMP IS ON FOR "); Serial.print(timeInSeconds); Serial.println(" seconds");
  delay((timeInSeconds*1000));
  turnOff();
}

void PumpControl::turnOff() {
  digitalWrite(pumpRelayPin, LOW);
  isPumpOn = false;
  Serial.println("❌PUMP IS OFF");
}

bool PumpControl::getPumpStatus(){
  return isPumpOn;
}