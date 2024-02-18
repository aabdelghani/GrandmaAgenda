#ifndef TIME_MANAGEMENT_H
#define TIME_MANAGEMENT_H

#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

void initializeTimeManagement(void);
time_t getVirtualTime(void);
void setSpeedFactor(int factor);
// Validates time format (HH:MM)
bool validateTimeFormat(const char* time);


#endif

