#include "unity.h"
#include "scheduler.h"

void setUp(void) {}
void tearDown(void) {}

void test_function_addActivity(void) {
    // Call addActivity or other functions you want to test
    // Use Unity's TEST_ASSERT or other macros to check results
    TEST_ASSERT_EQUAL_INT(1, addActivity("09:00", "10:00", "Test Activity"));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_addActivity);
    return UNITY_END();
}

