#ifndef SCHEDULER_H
#define SCHEDULER_H

void addActivity(const char* time, const char* description);
void queryActivity(const char* time);
void markActivityDone(const char* time);
void initializeScheduler();
void displayActivities();

#endif // SCHEDULER_H

