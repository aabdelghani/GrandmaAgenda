#include "ui.h"
#include "utils.h"
#include "scheduler.h"
#include "time_management.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include <sys/select.h> // for select()
#include <unistd.h>

int manualActivitiesAdded = 0; // Flag to track if manual activities were added

void startUserInteractionLoop() {
    char command[7];
    int speed;
    system("clear");
    printf("Welcome to GrandmaScheduler!\n");
    printf("Please start by adding activities.\n");

    while (1) {
        printf("\nCommands: add, display, run, exit\n> ");
        scanf("%s", command);

		if (strcmp(command, "add") == 0) {
			char option[10];
			printf("Do you want to add activities (m)anually or (a)utomatically?");
			scanf("%s", option);
			if (strcmp(option, "m") == 0) {
				manualActivitiesAdded = 1; // Set flag when manual activities are added
				char startTime[6], endTime[6], description[256];
				printf("Start Time (HH:MM): ");
				scanf("%s", startTime);
				printf("End Time (HH:MM): ");
				scanf("%s", endTime);
				printf("Description: ");
				scanf(" %[^\n]s", description); // Reads string with spaces
				addActivity(startTime, endTime, description);
			} else if (strcmp(option, "a") == 0) {
				readActivitiesFromCSV();
			}
		} else if (strcmp(command, "run") == 0) {
			if (!manualActivitiesAdded) { // Only add automatic activities if no manual ones were added
            	readActivitiesFromCSV();
        	}
            break;
        }
         else if (strcmp(command, "display") == 0) {
            displayActivities();
        } else if (strcmp(command, "exit") == 0) {
            printf("Exiting GrandmaScheduler...\n");
            break;
        }
    }

    system("clear");
    printf("Enter the speed factor for the program: ");
    scanf("%d", &speed);
    setSpeedFactor(speed);

    while (1) {
		system("clear"); // Clear the screen

		// Display the activities at the top
		printf("Scheduled Activities:\n");
		displayActivities();


		time_t now = getVirtualTime();
		char currentTime[6];
		strftime(currentTime, sizeof(currentTime), "%H:%M", localtime(&now));
		printf("\nCurrent time: %s\n", currentTime);

		// Check if an activity starts at the current time or is currently running
		for (int i = 0; i < activityCount; i++) {
			int startHour, startMinute, endHour, endMinute;
			int currentHour, currentMinute;
			sscanf(activities[i].startTime, "%d:%d", &startHour, &startMinute);
			sscanf(activities[i].endTime, "%d:%d", &endHour, &endMinute);
			sscanf(currentTime, "%d:%d", &currentHour, &currentMinute);

			int startTimeInMinutes = startHour * 60 + startMinute;
			int endTimeInMinutes = endHour * 60 + endMinute;
			int currentTimeInMinutes = currentHour * 60 + currentMinute;

			if (strcmp(activities[i].startTime, currentTime) == 0 && activities[i].done == 0) {
				printf("Activity just started: %s\n", activities[i].description);
				break;
			}
			else if (endTimeInMinutes - currentTimeInMinutes == 10 && activities[i].done == 0) {
				printf("Activity '%s' is about to end in 10 minutes.\n", activities[i].description);
				break;
			}	
			else if (currentTimeInMinutes > startTimeInMinutes && currentTimeInMinutes < endTimeInMinutes && activities[i].done == 0) {
				// This new condition checks if the current time is between the start and end times of an activity
				printf("Activity '%s' is currently running.\n", activities[i].description);
				break;
			}
		}


		fd_set readfds;
		struct timeval tv;
		FD_ZERO(&readfds);
		FD_SET(STDIN_FILENO, &readfds);
		tv.tv_sec = 3;
		tv.tv_usec = 0;

		if (select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv) > 0) {
			char time[6], response[256];
			scanf("%s", time);
			int activityFound = queryActivity(time); // Capture the return value
			if (activityFound) { // Only proceed if a valid activity was found
				printf("Are you doing it? (yes/no): ");
				scanf("%s", response);
				if (strcmp(response, "yes") == 0) {
				    markActivityDone(time);
				}
			}
		}


	}	
}

