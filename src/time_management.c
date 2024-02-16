#include "time_management.h"

static time_t programStartTime;
static int speedFactor = 1;

void initializeTimeManagement(void) {
    programStartTime = time(NULL);
}

time_t getVirtualTime() {
    time_t currentTime = time(NULL);
    double realTimeElapsed = difftime(currentTime, programStartTime);
    double virtualTimeElapsed = realTimeElapsed * speedFactor;
    
    return programStartTime + (time_t)virtualTimeElapsed;
}

void setSpeedFactor(int factor) {
    speedFactor = factor;
}

