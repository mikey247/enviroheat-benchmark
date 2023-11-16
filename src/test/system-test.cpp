#include <ctime>
#include "system-test.h"
#include "constants.h"
#include "temperature/temperature.h"
#include "relays/pump.h"
#include "relays/immersion.h"

SystemTest::SystemTest() {

}

TemperatureSensor temperatureSensor(DS18B20_PIN);
PumpControl pumpControl(PUMP_RELAY_PIN);
ImmersionControl immersionControl(IMMERSION_RELAY_PIN);

void runCycle(int durationMinutes, void (*action)()) {
    std::time_t startTime = std::time(0);
    int elapsedSeconds = 0;
    int times = 1;

    while (elapsedSeconds < (durationMinutes * 60)) {
        // Perform the action
        action();  
        times++;
        // Update elapsed time
        elapsedSeconds = difftime(std::time(0), startTime);
        Serial.println("THis cycle has run---- ");
        Serial.println(times);
    }
}

void SystemTest::warmUp() {
    // Implementation for warm-up stage
    // i.e turning on the resistance until TMAX is reached
    temperatureSensor.begin(); // initialize temperature reading
    immersionControl.begin();// initialize pump
    float temperature = temperatureSensor.readTemperature();
    immersionControl.turnOn(); // turn on heat
    while (temperature < TMAX) {
        temperature = temperatureSensor.readTemperature();
        delay(30000);  // Delay for 30 seconds
    }

    Serial.println("Warm up complete");
    immersionControl.turnOff(); //turn off heat
    return;
}

void SystemTest::idling() {
//      A) - From 0 to 1:30 a.m.:
//       - P = ON for 20s OFF every 60s
//       - R = ON (R respects the TMIN and TMAX thresholds)
    // runCycle(5, []() {
    //    runCycle(90, []() {
        // temperatureSensor.begin(); // initialize temperature reading
        // immersionControl.begin();// initialize pump
        // pumpControl.begin();
    //     //Serial.println("Controls initialized");
    //     float temperature = temperatureSensor.readTemperature();

    //     pumpControl.turnOnFor(20);
    //     Serial.println("Pump is on for 20 seconds");

    //     pumpControl.turnOff(); //turn pump off
    //     delay(60000);  // Delay for 60 seconds
    //     Serial.println("Pump is off for 60 seconds");
    //     Serial.println("The temperature is----");
    //     Serial.println(temperature);
    //     if (temperature <= TMIN) {
    //         immersionControl.turnOn();
    //         Serial.println("immersion is on");
    //         temperature++;
    //     } else if( temperature >= TMAX) {
    //         immersionControl.turnOff();
    //         Serial.println("Immersion is off");
    //     }
    // });

//     B) - From 1:30 a.m. to 11:35 a.m.:
//      - P = OFF
//      - R = OFF
    // runCycle(600, [](){
    //     pumpControl.begin(); // initialize pump 
    //     immersionControl.begin();// initialize immersion
    //     immersionControl.turnOff();
    //     pumpControl.turnOff();
    // });

    // // C) - From 11:35 a.m. to 12:05 p.m.:
    //  - P = ON
    //  - R = ON until 12:05 p.m. (R does not respect TMAX, i.e. ON continuously until 12:05 p.m.)
    // runCycle(31, [](){
    //     pumpControl.begin(); // initialize pump 
    //     immersionControl.begin(); // initialize immersion
    //     immersionControl.turnOn();
    //     pumpControl.turnOn();
    // });
}

void SystemTest::drainage() {
//     A) - From 12:00 a.m. to 3:30:34 p.m.:
//      - R = ON (R respects the TMIN and TMAX thresholds)
//      - P = ON if R is OFF while respecting the PON and POFF thresholds.
//      - P = OFF if R = ON
        temperatureSensor.begin(); // initialize temperature reading
        immersionControl.begin();// initialize pump
        pumpControl.begin();
        float temp = temperatureSensor.readTemperature();
        if(temp>=TMAX){
            immersionControl.turnOff();
            pumpControl.turnOn();
        }else if (temp<= TMIN){
            immersionControl.turnOn();
            pumpControl.turnOff();
        }
        
//     B) - From 3:30:34 p.m. to 12 p.m.:
//        - blocked valves
//        - P = OFF
//        - R = ON (R respects the TMIN and TMAX thresholds)

}

void SystemTest::v40() {
//  A)  - From 12:00 a.m. to 11:35 a.m.:
// - P = OFF
// - R = ON (R respects the TMIN and TMAX thresholds)

// B) - From 11:35 a.m. to 12:05 p.m.:
// - P = ON
// - R = ON until 12:05 p.m. (R does not respect TMAX)
// At 12:05 p.m.:
// - P = OFF
// - R = OFF
// - 10L/min valve open for 30 minutes

// When 30 minutes are reached, complete the system OFF.

}

// bool SystemTest::isTmaxReached() {
//     // Implementation to check if TMAX is reached
//     // Return true if TMAX is reached, false otherwise
// }

// std::string SystemTest::getPumpStatus() {
//     // Implementation to get the pump status
//     // Return "ON" or "OFF" based on the current state
// }

// std::string SystemTest::getResistanceStatus() {
//     // Implementation to get the resistance status
//     // Return "ON" or "OFF" based on the current state
// }
