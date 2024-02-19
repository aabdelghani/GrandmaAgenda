#define _XOPEN_SOURCE
#include "scheduler.h"
#include <ui.h>



Activity activities[10];
int activityCount = 0;




void initializeScheduler() {
    activityCount = 0; // Resets the scheduler
}


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
    int duration;
    /*if (endHour < startHour || (endHour == startHour && endMinute < startMinute)) {
        // If the end time is earlier than the start time, add 24 hours to the end time to handle the bedtime 
        duration = ((endHour + 24) * 60 + endMinute) - (startHour * 60 + startMinute);
    } else */{
        duration = (endHour * 60 + endMinute) - (startHour * 60 + startMinute);
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

int queryActivity(const char* time) {

    //pthread_mutex_lock(&queryActivity_mutex);

    int found = 0;
    // Validate time format before proceeding
    if (!validateTimeFormat(time)) {
        printf("Invalid time format. Please use HH:MM format.\n");
        return found;
    }
    
    char timePlus30[6]; // To store time 30 minutes ahead
    addMinutesToTime(time, 30, timePlus30);


	for (int i = 0; i < activityCount; i++) {
			found = 1;
		    if ((strcmp(activities[i].startTime, time) >= 0 && strcmp(activities[i].startTime, timePlus30) <= 0) || strcmp(activities[i].startTime, time) == 0) {
		        if (activities[i].done) {
		            printf("Chill, you already have %s.\n", activities[i].description);
		        } else {
		            printf("Activity from %s to %s: %s\n", activities[i].startTime, activities[i].endTime, activities[i].description);
		        }
		        return found;
		   }
	}
    
    if (!found) {
        printf("No activities found starting at %s or within the next 30 minutes.\n", time);
    }
    //pthread_mutex_unlock(&queryActivity_mutex);
    return found; // Return the result of the search

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
    //pthread_mutex_lock(&markActivityDone_mutex);
    int found = 0;
    // Validate time format before proceeding
    if (!validateTimeFormat(time)) {
        printf("Invalid time format. Please use HH:MM format.\n");
        return; // Do not proceed if the time format is invalid
    }

    char timePlus30[6]; // To store time 30 minutes ahead
    addMinutesToTime(time, 30, timePlus30);


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
    //pthread_mutex_unlock(&markActivityDone_mutex);

}

void displayActivities() {

    if (activityCount == 0) {
        printf("No activities have been added yet!\n");
        return; // Exit the function early since there's nothing to display
    }

    printf("Scheduled Activities:\n");
    for (int i = 0; i < activityCount; i++) {
        printf("%s - %s - %s - %s\n", activities[i].startTime, activities[i].endTime, activities[i].description, activities[i].done ? "Done" : "Not Done");
    }

}


