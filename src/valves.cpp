#include "valves.h"

ValveControl::ValveControl(int valveControlPin) : valveControlPin(valveControlPin){

}

void ValveControl::begin(){
    pinMode(valveControlPin, OUTPUT);
}

void ValveControl::turnOn(){
   digitalWrite(valveControlPin, HIGH);
   isValveOn = true;
   Serial.println("🌊🌊Valves are Open");
}

void ValveControl::turnOff(){
   digitalWrite(valveControlPin, LOW);
   isValveOn = false;
   Serial.println("❌❌Valves are closed");
}

bool ValveControl::getValveStatus(){
    return isValveOn;
}