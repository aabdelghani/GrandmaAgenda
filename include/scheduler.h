#ifndef SCHEDULER_H
#define SCHEDULER_H

void addActivity(const char* time, const char* description);
void queryActivity(const char* time);
void markActivityDone(const char* time);
void initializeScheduler();
void displayActivities();

typedef struct {
    char time[6]; // HH:MM format
    char description[256];
    int done; // 0 for not done, 1 for done
} Activity;

extern Activity activities[10];
extern int activityCount;


#endif // SCHEDULER_H

