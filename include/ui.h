#ifndef UI_H
#define UI_H
#include <pthread.h>
#include <stdio.h>
#include "time_management.h"
#include "scheduler.h"


void clearSection(int startLine, int endLine);
void startUserInteractionLoop();
void* displayActivitiesLoop(void* arg);
void* userInputLoop(void* arg);


#endif // UI_H

