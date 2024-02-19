
#include "ui.h"

int main() {
    startUserInteractionLoop();
    pthread_t displayThread, inputThread;

    // Start display activities thread
    if (pthread_create(&displayThread, NULL, displayActivitiesLoop, NULL)) {
        fprintf(stderr, "Error creating display activities thread\n");
        return 1;
    }

    // Start user input thread
    if (pthread_create(&inputThread, NULL, userInputLoop, NULL)) {
        fprintf(stderr, "Error creating user input thread\n");
        return 1;
    }

    // Wait for both threads to finish
    pthread_join(displayThread, NULL);
    pthread_join(inputThread, NULL);

    return 0;
}
