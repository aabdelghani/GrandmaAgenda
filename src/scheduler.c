#include "scheduler.h"
#include "utils.h" // validateTimeFormat
#include <stdio.h>
#include <string.h>



Activity activities[10];
int activityCount = 0;


void addActivity(const char* time, const char* description) {
    // Validate time format before proceeding
    if (!validateTimeFormat(time)) {
        printf("Invalid time format. Please use HH:MM format.\n");
        return; // Do not add the activity if the time format is invalid
    }

    if (activityCount < 10) {
        strcpy(activities[activityCount].time, time);
        strcpy(activities[activityCount].description, description);
        activities[activityCount].done = 0;
        activityCount++;
        printf("Activity added.\n");
    } else {
        printf("Maximum number of activities reached.\n");
    }
}

void queryActivity(const char* time) {
    // Validate time format before proceeding
    if (!validateTimeFormat(time)) {
        printf("Invalid time format. Please use HH:MM format.\n");
        return; // Do not proceed if the time format is invalid
    }

    for (int i = 0; i < activityCount; i++) {
        if (strcmp(activities[i].time, time) == 0) {
            if (activities[i].done) {
                printf("Chill, you already have %s.\n", activities[i].description);
            } else {
                printf("Activity at %s: %s\n", time, activities[i].description);
            }
            return;
        }
    }
    printf("No activities found at %s.\n", time);
}


void markActivityDone(const char* time) {
    // Validate time format before proceeding
    if (!validateTimeFormat(time)) {
        printf("Invalid time format. Please use HH:MM format.\n");
        return; // Do not proceed if the time format is invalid
    }

    for (int i = 0; i < activityCount; i++) {
        if (strcmp(activities[i].time, time) == 0 && activities[i].done == 0) {
            activities[i].done = 1;
            printf("Activity at %s marked as done.\n", time);
            return;
        }
    }
    printf("No activities found at %s to mark as done.\n", time);
}

void initializeScheduler() {
    activityCount = 0; // Resets the scheduler
}

void displayActivities() {
    printf("Scheduled Activities:\n");
    for (int i = 0; i < activityCount; i++) {
        printf("%s - %s - %s\n", activities[i].time, activities[i].description, activities[i].done ? "Done" : "Not Done");
    }
}

