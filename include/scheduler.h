#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <time_management.h>
#include <pthread.h>
#include "utils.h" // validateTimeFormat


typedef struct {
    char startTime[6]; // HH:MM format
    char endTime[6]; // HH:MM format
    char description[256];
    int done; // 0 for not done, 1 for done
} Activity;

extern Activity activities[10];
extern int activityCount;

void addActivity(const char* startTime, const char* endTime, const char* description);
int queryActivity(const char* time);
void markActivityDone(const char* time);
void initializeScheduler();
void displayActivities();
void addMinutesToTime(const char* time, int minutes, char* newTime);





#endif // SCHEDULER_H

