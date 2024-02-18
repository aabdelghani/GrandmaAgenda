#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "utils.h" // validateTimeFormat
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <time_management.h>

void addActivity(const char* startTime, const char* endTime, const char* description);
int queryActivity(const char* time);
void markActivityDone(const char* time);
void initializeScheduler();
void displayActivities();
void addMinutesToTime(const char* time, int minutes, char* newTime);

typedef struct {
    char startTime[6]; // HH:MM format
    char endTime[6]; // HH:MM format
    char description[256];
    int done; // 0 for not done, 1 for done
} Activity;

extern Activity activities[10];
extern int activityCount;


#endif // SCHEDULER_H

