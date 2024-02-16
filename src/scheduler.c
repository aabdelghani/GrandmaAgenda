#include "scheduler.h"
#include <stdio.h>
#include <string.h>

//simple activity structure
typedef struct {
    char time[6]; // HH:MM format
    char description[256];
    int done; // 0 for not done, 1 for done
} Activity;

// Fixed-size array to hold activities
#define MAX_ACTIVITIES 10
Activity activities[MAX_ACTIVITIES];
int activityCount = 0;

// Function to add an activity to the scheduler
void addActivity(const char* time, const char* description) {
    if (activityCount < MAX_ACTIVITIES) {
        strcpy(activities[activityCount].time, time);
        strcpy(activities[activityCount].description, description);
        activities[activityCount].done = 0;
        activityCount++;
    } else {
        printf("Maximum number of activities reached.\n");
    }
}

// Function to query activities by time
void queryActivity(const char* time) {
    for (int i = 0; i < activityCount; i++) {
        if (strcmp(activities[i].time, time) == 0) {
            printf("Activity at %s: %s\n", time, activities[i].description);
            return;
        }
    }
    printf("No activities found at %s.\n", time);
}

// function to mark an activity as done
void markActivityDone(const char* time) {
    for (int i = 0; i < activityCount; i++) {
        if (strcmp(activities[i].time, time) == 0) {
            activities[i].done = 1;
            printf("Activity at %s marked as done.\n", time);
            return;
        }
    }
    printf("No activities found at %s to mark as done.\n", time);
}

