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


// Function to check if input is available on stdin within a timeout period
int inputAvailable() {
    struct timeval tv;
    fd_set readfds;

    tv.tv_sec = 3; // 3 seconds timeout
    tv.tv_usec = 0; // 0 microseconds

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    // Check if input is available
    return select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv) > 0;
}

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

        for (int i = 0; i < activityCount; i++) {
            int startTimeInMinutes, endTimeInMinutes, currentTimeInMinutes;

            // Use the new function to parse times and convert them to minutes
            parseAndConvertTime(activities[i].startTime, activities[i].endTime, currentTime,
                                &startTimeInMinutes, &endTimeInMinutes, &currentTimeInMinutes);

            if (strcmp(activities[i].startTime, currentTime) == 0 && activities[i].done == 0) {
                printf("Activity just started: %s\n", activities[i].description);
                break;
            }
            else if (endTimeInMinutes - currentTimeInMinutes == 10 && activities[i].done == 0) {
                printf("Activity '%s' is about to end in 10 minutes.\n", activities[i].description);
                break;
            }   
            else if (currentTimeInMinutes > startTimeInMinutes && currentTimeInMinutes < endTimeInMinutes && activities[i].done == 0) {
                printf("Activity '%s' is currently running.\n", activities[i].description);
                break;
            }
        }

		sleep(1);
	}

    return NULL;
}


void* userInputLoop(void* arg) {
    while (1) {
        char time[6], response[256];
        int attempts = 0, maxAttempts = 5; // ask the user 5 times to enter yes/no

        pthread_mutex_lock(&printMutex);
        pthread_cond_wait(&canPrintCond, &printMutex);

		// Wait for the signal from displayActivitiesLoop
        //printf("Enter time (HH:MM), 'now' or 'exit' to quit: ");
		//printf("\033[14;1H");
		fflush(stdout);

        if(inputAvailable()){
            if (scanf("%5s", time) > 0) {
                if (strcmp(time, "exit") == 0) {
                    exit(EXIT_SUCCESS);
                } else if (strcmp(time, "now") == 0) {
                    // Use getVirtualTime to get the current time
                    time_t now = getVirtualTime();
                    // Format the virtual current time in "HH:MM" format
                    strftime(time, sizeof(time), "%H:%M", localtime(&now));
                    
                }
                // Use queryActivity to find the activity index
                int activityIndex = queryActivity(time);
                if (activityIndex == -1) {
                    // If no activity is found, continue to the next iteration
                    pthread_mutex_unlock(&printMutex);
                    continue;
                }

                int activityStatus = checkActivityStatus(activityIndex);

                    if (activityStatus) {
                        printf("Chill, you already have %s.\n", activities[activityIndex].description);
                    } else {
                        // New loop with timeout for "Are you doing it?" question
                        int gotResponse = 0;
                        while (!gotResponse && attempts < maxAttempts) {
                            printf("Are you doing it? (yes/no): ");
                            fflush(stdout);

                            if (inputAvailable()) { // Check for input with timeout
                                if (scanf("%255s", response) > 0) {
                                    gotResponse = 1; // Mark that we got a response
                                    if (strcmp(response, "yes") == 0) {
                                        markActivityDone(time);
                                        break; // Exit the loop once the activity is marked as done
                                    } else if (strcmp(response, "no") == 0) {
                                        break; // Exit the loop if the user explicitly says "no"
                                    } else {
                                        // If the response is neither "yes" nor "no", reset gotResponse to ask again
                                        gotResponse = 0;
                                    }
                                }
                            } else {
                                attempts++;
                                if (attempts < maxAttempts) {
                                    printf("\nWaiting for response... Attempt %d of %d\n", attempts, maxAttempts);
                                    //sleep(3); // Wait for 3 seconds before asking again
                                }
                            }
                        }
                    }
                pthread_mutex_unlock(&printMutex);
            } else {
                pthread_mutex_unlock(&printMutex);
            }
        }
        pthread_mutex_unlock(&printMutex);

        sleep(3);
    }
    return NULL;
}
