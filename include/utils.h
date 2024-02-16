#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

// Validates time format (HH:MM)
bool validateTimeFormat(const char* time);

void addAutomaticActivities(int descriptionsSize);

#endif // UTILS_H

