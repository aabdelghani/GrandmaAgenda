#include "ui.h"
#include "scheduler.h"
#include "time_management.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include <sys/select.h> // for select()
#include <unistd.h>

char* descriptions[] = {
    "Breakfast time",
    "Morning exercise",
    "Read a book",
    "Lunch time",
    "Take a nap",
    "Go for a walk",
    "Dinner time",
    "Watch TV",
    "Bedtime"
};

void startUserInteractionLoop() {
    char command[256], response[256];
    int speed;
    initializeTimeManagement(); // Initialize time management at the start
    initializeScheduler(); // Initialize or reset the scheduler
    system("clear");
    printf("Welcome to GrandmaScheduler!\n");
    printf("Please start by adding activities.\n");

    while (1) {
        printf("\nCommands: add, display, run, exit\n> ");
        scanf("%s", command);

        if (strcmp(command, "add") == 0) {
			char option[10];
			printf("Do you want to add activities manually or automatically? (manual/auto): ");
			scanf("%s", option);
			if (strcmp(option, "manual") == 0) {
				char time[6], description[256];
				printf("Time (HH:MM): ");
				scanf("%s", time);
				printf("Description: ");
				scanf(" %[^\n]s", description); // Reads string with spaces
				addActivity(time, description);
			} else if (strcmp(option, "auto") == 0) {
				int interval = 24 * 60 / 8; // Divide the day into 8 equal intervals
				for (int i = 0; i < 8; i++) {
				    char time[6];
				    int hour = (i * interval) / 60;
				    int minute = (i * interval) % 60;
				    sprintf(time, "%02d:%02d", hour, minute);
				    char* description = descriptions[rand() % (sizeof(descriptions) / sizeof(char*))];
				    addActivity(time, description);
				}
			}
    	}
 		else if (strcmp(command, "run") == 0) {
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

		// Check if an activity starts at the current time
		for (int i = 0; i < activityCount; i++) {
		    if (strcmp(activities[i].time, currentTime) == 0 && activities[i].done == 0) {
		        printf("Activity just started: %s\n", activities[i].description);
		        break;
		    }
		}

		// Check for user input during the 3-second interval
		fd_set readfds;
		struct timeval tv;
		FD_ZERO(&readfds);
		FD_SET(STDIN_FILENO, &readfds);
		tv.tv_sec = 3;
		tv.tv_usec = 0;

		if (select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv) > 0) {
		    char time[6], response[256];
		    scanf("%s", time);
		    queryActivity(time);
		    printf("Are you doing it? (yes/no): ");
		    scanf("%s", response);
		    if (strcmp(response, "yes") == 0) {
		        markActivityDone(time);
		    }
		}
	}

}

