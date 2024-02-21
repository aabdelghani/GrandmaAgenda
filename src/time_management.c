#include "time_management.h"

static time_t programStartTime;
static int speedFactor = 1;

void initializeTimeManagement(void) {
    programStartTime = time(NULL);
}

time_t getVirtualTime() {
    time_t currentTime = time(NULL);
    double realTimeElapsed = difftime(currentTime, programStartTime);
    // Apply the factor to the elapsed time
    double virtualTimeElapsed = realTimeElapsed * speedFactor;
    
    return programStartTime + (time_t)virtualTimeElapsed;
}


void setSpeedFactor(int factor) {
    speedFactor = factor;
}

bool validateTimeFormat(const char* time) {
    // Expected format: HH:MM
    if (strlen(time) != 5) return false;
    if (!isdigit(time[0]) || !isdigit(time[1]) || time[2] != ':' || !isdigit(time[3]) || !isdigit(time[4])) return false;

    int hours = (time[0] - '0') * 10 + (time[1] - '0');
    int minutes = (time[3] - '0') * 10 + (time[4] - '0');

    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) return false;

    return true;
}
