#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer {
public:
    Buzzer(int pin, int frequency);
    void turnOn();
    void turnOff();

private:
    int buzzerPin;
    int buzzerFrequency;
};

#endif
