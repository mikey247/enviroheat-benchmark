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



void runCycle(int durationMinutes, std::function<void()> action) {
    pumpControl.begin();
    immersionControl.begin();// initialize pump
    temperatureSensor.begin(); // initialize temperature reading

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

// Resistor R is ON up to TMAX.
// Once TMAX is reached, we move on to step 2. 
void SystemTest::warmUp() {
    Serial.println("WARM UP!!!!!");
    // Implementation for warm-up stage
    // i.e turning on the resistance until TMAX is reached
    float temperature = temperatureSensor.readTemperature();
    // float temperature = 35.34;
    Serial.println("Temp is : ");
    Serial.println( temperature);

    if (!immersionControl.getImmersionState()){
        immersionControl.begin();// initialize immersion
        immersionControl.turnOn(); // turn on heat
    }
        
    while (temperature < TMAX) {
        temperature = temperatureSensor.readTemperature();
        // temperature+=10;
        Serial.println("Temp is now : ");
        Serial.println(temperature);
        delay(10000);  // Delay for 30 seconds
    }

    Serial.println("Warm up complete");
    immersionControl.turnOff(); //turn off heat
    // return;
}

void SystemTest::idling() {
//      A) - From 0 to 1:30 a.m.:
//       - P = ON for 20s OFF every 60s
//       - R = ON (R respects the TMIN and TMAX thresholds)
    // runCycle(5, []() {
        Serial.println("IDLING!!!!");
       runCycle(IDLING_CYCLE_A, [this]() {
        Serial.println("IDLING_CYCLE_A");
        Serial.print("Pump and Heat are: "); Serial.print(pumpControl.getPumpStatus()?"ON":"OFF"); 
        Serial.print(" "); Serial.println(immersionControl.getImmersionState() ?"ON":"OFF");
        //Serial.println("Controls initialized");
        float temperature = temperatureSensor.readTemperature();

        pumpControl.turnOnFor(20);

        // pumpControl.turnOff(); //turn pump off
        this->respectTminTmax(temperature, false);
        delay(60000);  // Delay for 60 seconds
        Serial.println("Pump is off for 60 seconds");
        Serial.println("The temperature is----");
        Serial.println(temperature);
    });

//     B) - From 1:30 a.m. to 11:35 a.m.:
//      - P = OFF
//      - R = OFF
    runCycle(IDLING_CYCLE_B, [](){
            Serial.println("IDLING_CYCLE_B");
            Serial.print("Pump and Heat are: "); Serial.print(pumpControl.getPumpStatus()?"ON":"OFF"); 
            Serial.print(" "); Serial.println(immersionControl.getImmersionState() ?"ON":"OFF");
        if(immersionControl.getImmersionState() || pumpControl.getPumpStatus()){
            immersionControl.turnOff();
            pumpControl.turnOff();
            Serial.println("Pump and Heat are OFF!!!");
        }
        delay(10000);
    });

    // // C) - From 11:35 a.m. to 12:05 p.m.:
    //  - P = ON
    //  - R = ON until 12:05 p.m. (R does not respect TMAX, i.e. ON continuously until 12:05 p.m.)
    runCycle(IDLING_CYCLE_C, [](){
        Serial.println("IDLING_CYCLE_C");

        if(!immersionControl.getImmersionState()){
            immersionControl.turnOn();
        }
        if(!pumpControl.getPumpStatus()){
            pumpControl.turnOn();
        }
        Serial.println("Pump and Heat are ON!!!");
        delay(10000);
        Serial.print("Pump and Heat are: "); Serial.print(pumpControl.getPumpStatus()?"ON":"OFF"); 
        Serial.print(" "); Serial.println(immersionControl.getImmersionState() ?"ON":"OFF");
    });
}

void SystemTest::drainage() {
        Serial.println("DRAINAGE!!!!");

//     A) - From 12:00 a.m. to 3:30:34 p.m.:
//      - R = ON (R respects the TMIN and TMAX thresholds)
//      - P = ON if R is OFF while respecting the PON and POFF thresholds.
//      - P = OFF if R = ON
    runCycle(DRAINAGE_CYCLE_A, [this](){
            Serial.println("DRAINAGE_CYCLE_A");
            Serial.print("Pump and Heat are: "); Serial.print(pumpControl.getPumpStatus() ? "ON" : "OFF"); 
            Serial.print(" "); Serial.println(immersionControl.getImmersionState() ? "ON" : "OFF");

            float temperature = temperatureSensor.readTemperature();
            this->respectTminTmax(temperature, true);
            delay(10000);
    });
//     B) - From 3:30:34 p.m. to 12 p.m.:
//        - blocked valves
//        - P = OFF
//        - R = ON (R respects the TMIN and TMAX thresholds)
    runCycle(DRAINAGE_CYCLE_B, [this](){
        Serial.println("DRAINAGE_CYCLE_B");
        Serial.print("Pump and Heat are: "); Serial.print(pumpControl.getPumpStatus()?"ON":"OFF"); 
        Serial.print(" "); Serial.println(immersionControl.getImmersionState() ? "ON" : "OFF");

        if(pumpControl.getPumpStatus()){
        pumpControl.turnOff();
        }
        float temperature = temperatureSensor.readTemperature();
        this->respectTminTmax(temperature, false);  
        delay(10000);
    });
}

void SystemTest::v40() {
    Serial.println("V40!!!!!");
//  A)  - From 12:00 a.m. to 11:35 a.m.:
// - P = OFF
// - R = ON (R respects the TMIN and TMAX thresholds)
runCycle(V40_CYCLE_A, [this](){
    Serial.println("V40_CYCLE_A");
    Serial.print("Pump and Heat are: "); Serial.print(pumpControl.getPumpStatus() ? "ON" : "OFF"); 
    Serial.print(" "); Serial.println(immersionControl.getImmersionState() ? "ON" : "OFF");

    if (pumpControl.getPumpStatus()) {
    pumpControl.turnOff();
    }
    float temperature = temperatureSensor.readTemperature();
    this->respectTminTmax(temperature, false);  
    delay(10000);
});

// B) - From 11:35 a.m. to 12:05 p.m.:
// - P = ON
// - R = ON until 12:05 p.m. (R does not respect TMAX)
// At 12:05 p.m.:
// - P = OFF
// - R = OFF
// - 10L/min valve open for 30 minutes
// When 30 minutes are reached, complete the system OFF.
runCycle(V40_CYCLE_B, [](){
    Serial.println("V40_CYCLE_b");
    Serial.print("Pump and Heat are: "); Serial.print(pumpControl.getPumpStatus() ? "ON" : "OFF"); 
    Serial.print(" "); Serial.println(immersionControl.getImmersionState() ? "ON" : "OFF");

    pumpControl.turnOn();
    immersionControl.turnOn();
    delay(10000);
    // delay(1800000);//delay for 30 minutes i.e (till 12:05pm)
    pumpControl.turnOff();
    immersionControl.turnOff();

    // TODO: turn on valves
    Serial.println("Valves turn on!!");
    delay(10000);
    // delay(1800000);// delay another 30 minutes
    //TODO :System switches off
    Serial.println("SYSTEM SHUTDOWN!!");
});
}

void SystemTest::respectTminTmax(float temperature, bool pumpEngaged) {
    Serial.println("RESPECT TMIN AND TMAX");
    Serial.print("THE TEMPERATURE HERE IS::: "); Serial.println(temperature);
    if(temperature>=TMAX){
        if (immersionControl.getImmersionState()){// switch immersion off only if it's on
            immersionControl.turnOff();
            if(pumpEngaged){
                pumpControl.turnOn(); 
            }   
        }    
    } else if (temperature <= TMIN){
       if (!immersionControl.getImmersionState()){ // switch on immersion only if its off
            immersionControl.turnOn();
           if(pumpEngaged) {
             pumpControl.turnOff();    
           }
        }
    }
}
