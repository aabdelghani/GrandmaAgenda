#include "ui.h"
#include "scheduler.h"
#include <stdio.h>
#include <string.h>

void startUserInteractionLoop() {
    char input[256];
    printf("Welcome to GrandmaScheduler!\n");

    while (1) {
        printf("\nEnter a command (add, query, mark, exit): ");
        scanf("%s", input);

        if (strcmp(input, "add") == 0) {
            char time[6], description[256];
            printf("Enter time (HH:MM): ");
            scanf("%s", time);
            printf("Enter description: ");
            scanf("%s", description); 
            addActivity(time, description);
        } else if (strcmp(input, "query") == 0) {
            char time[6];
            printf("Enter time (HH:MM): ");
            scanf("%s", time);
            queryActivity(time);
        } else if (strcmp(input, "mark") == 0) {
            char time[6];
            printf("Enter time (HH:MM) of the activity to mark as done: ");
            scanf("%s", time);
            markActivityDone(time);
        } else if (strcmp(input, "exit") == 0) {
            break;
        } else {
            printf("Unknown command.\n");
        }
    }

    printf("Exiting GrandmaScheduler.\n");
}

