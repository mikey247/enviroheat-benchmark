#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <Arduino.h>

// PINS
const int IMMERSION_RELAY_PIN = D1;
const int PUMP_RELAY_PIN = D2;
const int DS18B20_PIN = D3;
// THRESHOLDS
const float TMAX = 65.22;  
const float TMIN = 56.2; 

// // CYCLE TIMES
// const int IDLING_CYCLE_A = 90;
// const int IDLING_CYCLE_B = 615;
// const int IDLING_CYCLE_C = 30;

// const int DRAINAGE_CYCLE_A = 930;
// const int DRAINAGE_CYCLE_B = 510;

// const int V40_CYCLE_A = 695 ;
// const int V40_CYCLE_B = 65;


// CYCLE TIMES
const int IDLING_CYCLE_A = 3;
const int IDLING_CYCLE_B = 3;
const int IDLING_CYCLE_C = 2;

const int DRAINAGE_CYCLE_A = 5;
const int DRAINAGE_CYCLE_B = 5;

const int V40_CYCLE_A = 9 ;
const int V40_CYCLE_B = 2;

#endif 