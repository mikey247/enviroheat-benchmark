#include <Arduino.h>
#include <unity.h>
#include "system.h"  // Replace with your actual header file

SystemTest systemTest;  // Replace with your actual class instantiation

void test_warm_up() {
    systemTest.warmUp();
    TEST_ASSERT_TRUE(systemTest.isTmaxReached());
}

void test_idling() {
    systemTest.idling();
    TEST_ASSERT_EQUAL_STRING("ON", systemTest.getPumpStatus().c_str());
    TEST_ASSERT_EQUAL_STRING("ON", systemTest.getResistanceStatus().c_str());

    // Add more assertions based on your specifications
}

void test_drainage() {
    systemTest.drainage();
    TEST_ASSERT_EQUAL_STRING("ON", systemTest.getResistanceStatus().c_str());

    // Add more assertions based on your specifications
}

void test_v40() {
    systemTest.v40();
    TEST_ASSERT_EQUAL_STRING("OFF" or "ON", systemTest.getPumpStatus().c_str());
    TEST_ASSERT_EQUAL_STRING("OFF", systemTest.getResistanceStatus().c_str());

    // Add more assertions based on your specifications
}

void setup() {
    delay(2000);  // Give some time for the Serial Monitor to open
    UNITY_BEGIN(); // Initialize Unity test framework
    RUN_TEST(test_warm_up);
    RUN_TEST(test_idling);
    RUN_TEST(test_drainage);
    RUN_TEST(test_v40);
    UNITY_END();   // Finish the test
}

void loop() {
    // Nothing here for a one-time test
}
