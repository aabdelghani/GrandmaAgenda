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
volatile int isInputMode = 0;
pthread_mutex_t inputModeMutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t printMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t canPrintCond = PTHREAD_COND_INITIALIZER;

void moveCursorToPosition(int line, int column) {
    printf("\033[%d;%dH", line, column);
    fflush(stdout); // Ensure the command is processed by the terminal immediately
}

void clearSection(int startLine, int endLine) {
    // Move cursor to the start of the section
    printf("\033[%d;1H", startLine); // Move cursor to startLine, column 1

    // Clear each line
    for (int i = startLine; i <= endLine; i++) {
        printf("\033[2K"); // Clear the entire line
        if (i < endLine) {
            printf("\033[1B"); // Move cursor down one line
        }
    }

    // Optionally, move cursor back to the start of the section or to a new desired position
    printf("\033[%d;1H", startLine); // Position cursor at the beginning of cleared section
}

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
}

void* displayActivitiesLoop(void* arg) {
	while(1){
        
		pthread_mutex_lock(&printMutex);
		system("clear");
		printf("Scheduled Activities:\n");
		displayActivities();

		time_t now = getVirtualTime();
		char currentTime[6];
		strftime(currentTime, sizeof(currentTime), "%H:%M", localtime(&now));
		printf("\nCurrent time: %s\n", currentTime);
        pthread_cond_signal(&canPrintCond);
		pthread_mutex_unlock(&printMutex);

		//pthread_mutex_lock(&inputModeMutex);
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

		//pthread_mutex_unlock(&inputModeMutex);
		sleep(3);
	}

    return NULL;
}


/*

*/
void* userInputLoop(void* arg) {
    while (1) {
        char time[6], response[256];

        pthread_mutex_lock(&printMutex);
        pthread_cond_wait(&canPrintCond, &printMutex);

		// Wait for the signal from displayActivitiesLoop
        printf("Enter time (HH:MM), 'now' or 'exit' to quit: ");
		//printf("\033[14;1H");
		fflush(stdout);
		pthread_mutex_unlock(&printMutex);

        
        if (scanf("%5s", time) > 0) {
            pthread_mutex_lock(&inputModeMutex);
            if (strcmp(time, "exit") == 0) {
                //pthread_mutex_unlock(&inputModeMutex);
                exit(EXIT_SUCCESS);
            } /*else if(strcmp(time, "now") == 0){

            }*/
            // Use queryActivity to find the activity index
            int activityIndex = queryActivity(time);
            if (activityIndex == -1) {
                // If no activity is found, continue to the next iteration
                pthread_mutex_unlock(&inputModeMutex);
                continue;
            }

            int activityStatus = checkActivityStatus(activityIndex);

            if (activityStatus) {
                printf("Chill, you already have %s.\n", activities[activityIndex].description);
            } else {
                // Ask if the user is doing it until they say "yes" or "no"
                do {
                    printf("Are you doing it? (yes/no): ");
                    fflush(stdout);
                    scanf("%255s", response);
                    fflush(stdout);
                    if (strcmp(response, "yes") == 0) {
                        markActivityDone(time);
                        break; // Exit the loop once the activity is marked as done
                    }
                } while (strcmp(response, "no") != 0); // Continue asking if the response is not "no"

            }

            pthread_mutex_unlock(&inputModeMutex);
            sleep(3); // Wait a bit before the next prompt, adjust as needed
            } else {
                pthread_mutex_unlock(&inputModeMutex); // Ensure to unlock if no input is taken
            }
		    sleep(3);
    }
    return NULL;
}
