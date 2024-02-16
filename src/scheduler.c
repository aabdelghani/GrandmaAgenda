#define _XOPEN_SOURCE
#include "scheduler.h"
#include "utils.h" // validateTimeFormat
#include <stdio.h>
#include <string.h>
#include <time.h>


Activity activities[10];
int activityCount = 0;


void addActivity(const char* startTime, const char* endTime, const char* description) {
    // Validate time format before proceeding
    if (!validateTimeFormat(startTime) || !validateTimeFormat(endTime)) {
        printf("Invalid time format. Please use HH:MM format.\n");
        return; // Do not add the activity if the time format is invalid
    }

    // Validate that the start time is before the end time and the duration is at least 30 minutes
    int startHour, startMinute, endHour, endMinute;
    sscanf(startTime, "%d:%d", &startHour, &startMinute);
    sscanf(endTime, "%d:%d", &endHour, &endMinute);
    int duration = (endHour * 60 + endMinute) - (startHour * 60 + startMinute);
    if (duration <= 0 || duration < 30) {
        printf("Invalid time range. The end time must be at least 30 minutes after the start time.\n");
        return;
    }

    if (activityCount < 10) {
        strcpy(activities[activityCount].startTime, startTime);
        strcpy(activities[activityCount].endTime, endTime);
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
        return;
    }
    
    char timePlus30[6]; // To store time 30 minutes ahead
    addMinutesToTime(time, 30, timePlus30);

    int found = 0;
    for (int i = 0; i < activityCount; i++) {
        if ((strcmp(activities[i].startTime, time) <= 0 && strcmp(activities[i].endTime, time) >= 0) ||
            (strcmp(activities[i].startTime, time) >= 0 && strcmp(activities[i].startTime, timePlus30) <= 0)) {
            printf("Activity from %s to %s: %s\n", activities[i].startTime, activities[i].endTime, activities[i].description);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("No activities found starting at %s or within the next 30 minutes.\n", time);
    }
}


// Implementation of addMinutesToTime function
void addMinutesToTime(const char* time, int minutes, char* newTime) {
    struct tm tmTime;
    strptime(time, "%H:%M", &tmTime); // Parse time into tm structure
    tmTime.tm_min += minutes; // Add minutes
    mktime(&tmTime); // Normalize tm structure
    
    strftime(newTime, 6, "%H:%M", &tmTime); // Format back to string
}
void markActivityDone(const char* time) {
    // Validate time format before proceeding
    if (!validateTimeFormat(time)) {
        printf("Invalid time format. Please use HH:MM format.\n");
        return; // Do not proceed if the time format is invalid
    }

    char timePlus30[6]; // To store time 30 minutes ahead
    addMinutesToTime(time, 30, timePlus30);

    int found = 0;
    for (int i = 0; i < activityCount; i++) {
        // Check if the activity is ongoing or starts within the next 30 minutes
        if ((strcmp(activities[i].startTime, time) <= 0 && strcmp(activities[i].endTime, time) >= 0) ||
            (strcmp(activities[i].startTime, time) >= 0 && strcmp(activities[i].startTime, timePlus30) <= 0)) {
            if (activities[i].done == 0) {
                activities[i].done = 1;
                printf("Activity at %s to %s marked as done.\n", activities[i].startTime, activities[i].endTime);
                found = 1;
                break; // Stop after marking the first matching activity as done
            }
        }
    }

    if (!found) {
        printf("No activities found starting at %s or within the next 30 minutes to mark as done.\n", time);
    }
}

void initializeScheduler() {
    activityCount = 0; // Resets the scheduler
}

void displayActivities() {
    printf("Scheduled Activities:\n");
    for (int i = 0; i < activityCount; i++) {
        printf("%s - %s - %s - %s\n", activities[i].startTime, activities[i].endTime, activities[i].description, activities[i].done ? "Done" : "Not Done");
    }
}

