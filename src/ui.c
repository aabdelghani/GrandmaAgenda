#include "ui.h"
#include "scheduler.h"
#include "time_management.h"
#include <stdio.h>
#include <string.h> 


void startUserInteractionLoop() {
    char command[256];
	initializeTimeManagement(); // Initialize time management at the start
    initializeScheduler(); // Initialize or reset the scheduler
	system("clear");
    printf("Welcome to GrandmaScheduler!\n");
    while (1) {
        printf("\nCommands: add, query, mark, display, exit\n> ");
        scanf("%s", command);

        if (strcmp(command, "add") == 0) {
            char time[6], description[256];
            printf("Time (HH:MM): ");
            scanf("%s", time);
            printf("Description: ");
            scanf(" %[^\n]s", description); // Reads string with spaces
            addActivity(time, description);
        } else if (strcmp(command, "query") == 0) {
            char time[6];
            printf("Time (HH:MM): ");
            scanf("%s", time);
            queryActivity(time);
        } else if (strcmp(command, "mark") == 0) {
            char time[6];
            printf("Time (HH:MM) of the activity to mark as done: ");
            scanf("%s", time);
            markActivityDone(time);
        } else if (strcmp(command, "display") == 0) {
            displayActivities();
        } else if (strcmp(command, "exit") == 0) {
            printf("Exiting GrandmaScheduler...\n");
            break;
        } else if (strcmp(command, "speed") == 0) {
            int factor;
            printf("Enter new speed factor (1=normal, >1=faster, <1=slower): ");
            scanf("%d", &factor);
            setSpeedFactor(factor);
            printf("Speed factor set to %d.\n", factor);
        }else {
            printf("Invalid command.\n");
        }
    }
}

