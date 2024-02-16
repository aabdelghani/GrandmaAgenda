#ifndef TIME_MANAGEMENT_H
#define TIME_MANAGEMENT_H

#include <time.h>

void initializeTimeManagement(void);
time_t getVirtualTime(void);
void setSpeedFactor(int factor);

#endif

