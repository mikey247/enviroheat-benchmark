#include <Arduino.h>
#include "temperature/temperature.h"
#include "relays/pump.h"
#include "relays/immersion.h"
#include "test-funcs/system-test.h"
#include "buzzer.h"

// immersion : D1
// pump : D2
// sensor data : D3
// buzzer : D7
// TX from the node goes on the screen RX
// RX from the node goes on the screen TX

// put function declarations here:

const int IMMERSION_RELAY_PIN = D1;
const int PUMP_RELAY_PIN = D2;
const int DS18B20_PIN = D3;
const int BUZZER_PIN = D7;

// #define PUMP_RELAY_PIN D2
// #define DS18B20_PIN D3

// TemperatureSensor temperatureSensor(DS18B20_PIN);
// PumpControl pumpControl(PUMP_RELAY_PIN);
// ImmersionControl immersionControl(IMMERSION_RELAY_PIN);
SystemTest systemTest;
Buzzer buzzer(BUZZER_PIN, 1000);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(IMMERSION_RELAY_PIN, OUTPUT);
  pinMode(PUMP_RELAY_PIN, OUTPUT);

  Serial.begin(9600);

  systemTest.warmUp();
  buzzer.turnOn();
  delay(1000);
  buzzer.turnOff();

  systemTest.idling();
  buzzer.turnOn();
  delay(1000);
  buzzer.turnOff();

  // systemTest.drainage();
  // buzzer.turnOn();
  // delay(1000);
  // buzzer.turnOff();
  
  // systemTest.v40();
  // buzzer.turnOn();
  // delay(1000);
  // buzzer.turnOff();
  
  // temperatureSensor.begin();// Initialize the temperature sensor
  // pumpControl.begin(); // Initialize the pump control relay
  // immersionControl.begin(); // Initialize heat control relay
}

void loop() {  
  // digitalWrite(LED_BUILTIN,HIGH);
  // Serial.println("HIGH");
  // // digitalWrite(IMMERSION_RELAY_PIN, HIGH);
  // delay(1000);
  
  // digitalWrite(PUMP_RELAY_PIN, HIGH);
  // delay(1000);

  // digitalWrite(LED_BUILTIN, LOW);
  // Serial.println("LOW");
  // // digitalWrite(IMMERSION_RELAY_PIN, LOW);
  // // digitalWrite(PUMP_RELAY_PIN, LOW);
  // // delay(1000);


  // systemTest.warmUp();
  // systemTest.idling();
  // systemTest.drainage();
  // systemTest.v40();
  // delay(1000);
}

// put function definitions here: