#include <unity.h>
#include "scheduler.h"
#include "utils.h"
#include "stdio.h"
void setUp(void) {
    // Reset the scheduler to a known state before each test
    initializeScheduler();
}

void tearDown(void) {
    // Any cleanup code after each test (if necessary)
}

// Test adding a valid activity successfully modifies the activities array
void test_addActivity_ValidInput(void) {
    addActivity("09:00", "10:00", "Morning Run");
    TEST_ASSERT_EQUAL_STRING("09:00", activities[0].startTime);
    TEST_ASSERT_EQUAL_STRING("10:00", activities[0].endTime);
    TEST_ASSERT_EQUAL_STRING("Morning Run", activities[0].description);
    TEST_ASSERT_EQUAL_INT(0, activities[0].done); // Assuming 0 means not done
    TEST_ASSERT_EQUAL_INT(1, activityCount); // Ensure activity count is incremented
}

// Test that adding an activity with invalid time format does not change activity count
void test_addActivity_InvalidTimeFormat(void) {
    addActivity("9:00", "10:00", "Invalid Time Format Activity");
    TEST_ASSERT_EQUAL_INT(0, activityCount); // Activity should not be added, count remains 0
}

// Test adding more activities than the array can hold
void test_addActivity_ExceedsCapacity(void) {
    for (int i = 0; i < 10; i++) {
        addActivity("09:00", "10:00", "Activity");
    }
    // Attempt to add one more activity beyond the capacity
    addActivity("09:00", "10:00", "Extra Activity");
    TEST_ASSERT_EQUAL_INT(10, activityCount); // Count should not exceed 10
    // Optionally, check that the last valid activity is as expected
    TEST_ASSERT_EQUAL_STRING("Activity", activities[9].description);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_addActivity_ValidInput);
    RUN_TEST(test_addActivity_InvalidTimeFormat);
    RUN_TEST(test_addActivity_ExceedsCapacity);
    return UNITY_END();
}

