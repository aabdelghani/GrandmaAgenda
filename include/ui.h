#ifndef UI_H
#define UI_H
#include <pthread.h>
#include <stdio.h>




void startUserInteractionLoop();
void* displayActivitiesLoop(void* arg);
void* userInputLoop(void* arg);


#endif // UI_H

