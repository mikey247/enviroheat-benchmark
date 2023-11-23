#include "buzzer.h"

Buzzer::Buzzer(int pin, int frequency) : buzzerPin(pin), buzzerFrequency(frequency) {
    pinMode(buzzerPin, OUTPUT);
}

void Buzzer::turnOn() {
    tone(buzzerPin, buzzerFrequency);
}

void Buzzer::turnOff() {
    noTone(buzzerPin);
}
