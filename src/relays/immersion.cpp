  #include "immersion.h"
  #include "constants.h"

ImmersionControl::ImmersionControl(int immersionRelayPin) : immersionRelayPin(immersionRelayPin),isImmersionOn(false) {
  
}

void ImmersionControl::begin() {
  pinMode(immersionRelayPin, OUTPUT);
}

void ImmersionControl::turnOn() {
  digitalWrite(immersionRelayPin, HIGH);
  isImmersionOn = true;
  Serial.print(ImmersionStatusField+"ON");
  Serial.println("🔥IMMERSION IS ON");
}

void ImmersionControl::turnOnFor(int timeInSeconds){
 turnOn();
 Serial.print("🔥IMMERSION IS ON FOR "); Serial.print(timeInSeconds); Serial.print(" seconds");
 delay((timeInSeconds*1000));
 turnOff();
}

void ImmersionControl::turnOff() {
  digitalWrite(immersionRelayPin, LOW);
  isImmersionOn = false;
  Serial.print(ImmersionStatusField+"OFF");
  Serial.println("❌IMMERSION IS OFF");
}

bool ImmersionControl::getImmersionState() {
  return isImmersionOn;
}