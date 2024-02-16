#include "scheduler.h"
#include "unity.h"

// Define setUp and tearDown functions
void setUp(void) { /* Do nothing */ }
void tearDown(void) { /* Do nothing */ }

void test_addActivity_IncreasesActivityCount(void) {
    int initialCount = activityCount;
    addActivity("09:00", "10:00", "Morning Jog");
    TEST_ASSERT_EQUAL_INT(initialCount + 1, activityCount);
}

// Main function
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_addActivity_IncreasesActivityCount);
    return UNITY_END();
}

